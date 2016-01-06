#include "State.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "File.h"
#include "Game/Map.h"
#include "Game/Object/Player.h"
#include "Image/Sprite.h"
#include "Point.h"

State::State()
:	object_image_(0), map_(0),
	player1p_(0)
{
	// object_image_, and player1p_ will be loaded at State::load

	map_ = new Game::Map(19, 15);
}

State::~State()
{
	SAFE_DELETE(object_image_);
	SAFE_DELETE(map_);
	SAFE_DELETE(player1p_);
}

void State::load(Constants::PlayMode)
{
	ASSERT(!object_image_);
	object_image_ = new Image::Sprite(File("data/image/BakudanBitoImage.dds"), 4, 4);
	map_->load();

	ASSERT(!player1p_);
	player1p_ = new Game::Object::Player(0, Point(1, 1));
}

void State::update()
{
	GameLib::Framework f = GameLib::Framework::instance();
	unsigned now = f.time();

	Point player1p_point = player1p_->point();
	Point player1p_direction(0, 0);

	if (f.isKeyOn('A') && !map_->is_block(Point(player1p_point, -1, 0)))
	{
		player1p_direction.set_xy(-1, 0);
	}
	else if (f.isKeyOn('S') && !map_->is_block(Point(player1p_point, 1, 0)))
	{
		player1p_direction.set_xy(1, 0);
	}
	else if (f.isKeyOn('W') && !map_->is_block(Point(player1p_point, 0, -1)))
	{
		player1p_direction.set_xy(0, -1);
	}
	else if (f.isKeyOn('Z') && !map_->is_block(Point(player1p_point, 0, 1)))
	{
		player1p_direction.set_xy(0, 1);
	}

	player1p_->move_to(player1p_direction, now);
	player1p_->tick(now);
}

void State::draw() const
{
	map_->draw(*object_image_);
	player1p_->draw(*object_image_);
}
