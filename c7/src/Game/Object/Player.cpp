#include "Game/Object/Player.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "Game/Event/Move.h"
#include "Image/Sprite.h"
#include "Point.h"
#include "Size.h"
#include "State.h"

namespace Game
{

namespace Object
{

Player::Player(int index, const Point& point)
:	Parent(point),
	player_index_(index), move_event_(0) {}
Player::~Player() { SAFE_DELETE(move_event_); }

namespace
{

State::ObjectImage get_object_image_id(int player_index)
{
	if (player_index == 0)
	{
		return State::OBJECT_IMAGE_PLAYER1;
	}
	return State::OBJECT_IMAGE_PLAYER2;
}

} // namespace -

void Player::move_to(const Point& new_diff, unsigned now)
{
	if (move_event_ && move_event_->did_complete())
	{
		SAFE_DELETE(move_event_);
	}

	if (new_diff.scalar() == 0)
	{
		return;
	}

	if (!move_event_)
	{
		move_event_ = new Game::Event::Move(now, Parent::point(), new_diff);
		Parent::point(Parent::point() + new_diff);
		return;
	}

	if (!move_event_->can_reverse_by(new_diff))
	{
		return;
	}

	move_event_->reverse();
	Parent::point(Parent::point() + new_diff);
}

void Player::tick(unsigned now)
{
	if (!move_event_)
	{
		return;
	}

	move_event_->tick(now);
}

void Player::draw(const Image::Sprite& image)  const
{
	GameLib::Framework f = GameLib::Framework::instance();
	Size size = Size(f.width(), f.height());
	unsigned* vram = f.videoMemory();

	if (!move_event_)
	{
		image.copy_alpha_blend(	get_object_image_id(player_index_),
								Parent::point(),
								size,
								vram);
		return;
	}

	image.copy_alpha_blend(	get_object_image_id(player_index_),
							*move_event_,
							size,
							vram);
}

void Player::pause(unsigned now)
{
	if (move_event_)
	{
		move_event_->pause(now);
	}
}

void Player::resume(unsigned now)
{
	if (move_event_)
	{
		move_event_->resume(now);
	}
}

} // namespace Object

} // namespace Game
