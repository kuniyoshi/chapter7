#include "State.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "File.h"
#include "Game/Map.h"
#include "Game/Object/Player.h"
#include "Image/Sprite.h"
#include "Piece.h"
#include "Point.h"
#include "collision.h"

#include <sstream>

State::State()
:	object_image_(0), map_(0),
	player1p_(0), player2p_(0),
	play_mode_(Constants::PlayMode1P)
{
	// State::load will be load object_image_, and player1p_

	map_ = new Game::Map(19, 15);
}

State::~State()
{
	SAFE_DELETE(object_image_);
	SAFE_DELETE(map_);
	SAFE_DELETE(player1p_);
	SAFE_DELETE(player2p_);
}

void State::load(Constants::PlayMode play_mode)
{
	play_mode_ = play_mode;

	ASSERT(!object_image_);
	object_image_ = new Image::Sprite(File("data/image/BakudanBitoImage.dds"), 4, 4);
	map_->load();

	ASSERT(!player1p_);
	player1p_ = new Game::Object::Player(0, Point(2, 1), *object_image_);

	if (play_mode_ == Constants::PlayMode2P)
	{
		ASSERT(!player2p_);
		// player2p_ = new Game::Object::Player(1, Point(17, 13), *object_image_);
		player2p_ = new Game::Object::Player(1, Point(1, 2), *object_image_);
	}
}

void State::update()
{
	GameLib::Framework f = GameLib::Framework::instance();
	unsigned now = f.time();

	player1p_->clear_volatility_condition();

	if (player2p_)
	{
		player2p_->clear_volatility_condition();
	}

	Point player1p_point = player1p_->point();
	Point player1p_direction(0, 0);

	if (f.isKeyOn('A') && !map_->can_not_invade(Point(player1p_point, -1, 0)))
	{
		player1p_direction.set_xy(-1, 0);
	}
	else if (f.isKeyOn('S') && !map_->can_not_invade(Point(player1p_point, 1, 0)))
	{
		player1p_direction.set_xy(1, 0);
	}
	else if (f.isKeyOn('W') && !map_->can_not_invade(Point(player1p_point, 0, -1)))
	{
		player1p_direction.set_xy(0, -1);
	}
	else if (f.isKeyOn('Z') && !map_->can_not_invade(Point(player1p_point, 0, 1)))
	{
		player1p_direction.set_xy(0, 1);
	}

	player1p_->move_to(player1p_direction, now);

	if (player2p_)
	{
		Point player2p_point = player2p_->point();
		Point player2p_direction(0, 0);

		if (f.isKeyOn('H') && !map_->can_not_invade(Point(player2p_point, -1, 0)))
		{
			player2p_direction.set_xy(-1, 0);
		}
		else if (f.isKeyOn('J') && !map_->can_not_invade(Point(player2p_point, 0, 1)))
		{
			player2p_direction.set_xy(0, 1);
		}
		else if (f.isKeyOn('K') && !map_->can_not_invade(Point(player2p_point, 0, -1)))
		{
			player2p_direction.set_xy(0, -1);
		}
		else if (f.isKeyOn('L') && !map_->can_not_invade(Point(player2p_point, 1, 0)))
		{
			player2p_direction.set_xy(1, 0);
		}

		player2p_->move_to(player2p_direction, now);

		unsigned ms_to_collision(0);
		bool will_collision_occur
		= collision::set_ms_at_collision_occur(	player1p_->make_piece(),
												player2p_->make_piece(),
												&ms_to_collision);

		if (will_collision_occur)
		{
			if (!player1p_->does_direction_open(*player2p_, ms_to_collision))
			{
				player1p_->stop_until(ms_to_collision);
			}

			if (!player2p_->does_direction_open(*player1p_, ms_to_collision))
			{
				player2p_->stop_until(ms_to_collision);
			}
		}
	}

	player1p_->tick(now);

	if (player2p_)
	{
		player2p_->tick(now);
	}
}

void State::draw() const
{
	map_->draw(*object_image_);
	player1p_->draw(*object_image_);

	if (player2p_)
	{
		player2p_->draw(*object_image_);
	}
}

void State::pause()
{
	GameLib::Framework f = GameLib::Framework::instance();
	unsigned now(f.time());
	player1p_->pause(now);

	if (player2p_)
	{
		player2p_->pause(now);
	}
}

void State::resume()
{
	GameLib::Framework f = GameLib::Framework::instance();
	unsigned now(f.time());
	player1p_->resume(now);

	if (player2p_)
	{
		player2p_->resume(now);
	}
}
