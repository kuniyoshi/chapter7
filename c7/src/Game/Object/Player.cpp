#include "Game/Object/Player.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "Game/Container/Bomb.h"
#include "Game/Event/Dying.h"
#include "Game/Event/Move.h"
#include "Game/Map.h"
#include "Image/Sprite.h"
#include "Piece.h"
#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "State.h"

namespace Game
{

namespace Object
{

const int Player::MaxBombs = 5;

namespace
{

const unsigned MsToCompleteMoving   = 1000;

} // namespace -

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

Player::Player(int index, const Point& point, const Image::Sprite& image)
:   Parent(point),
    player_index_(index),
    dying_event_(0),move_event_(0),
    rect_(), ms_to_collision_(0), will_stop_(false), is_stopping_(false),
    power_(1), max_bombs_(1)
{
    image.set_inner_area_of(get_object_image_id(index), &rect_);
}

Player::~Player()
{
    SAFE_DELETE(dying_event_);
    SAFE_DELETE(move_event_);
}

int Player::player_index() const { return player_index_; }

void Player::ms_to_collision(unsigned new_value) { ms_to_collision_ = new_value; }

bool Player::is_stopping() const { return is_stopping_; }

void Player::prepare()
{
    // clear volatility condition
    {
        ms_to_collision_ = 0;
        will_stop_ = false;
    }

    // complete event
    {
        if (move_event_ && move_event_->did_complete())
        {
            SAFE_DELETE(move_event_);
        }

        if (dying_event_ && dying_event_->did_complete())
        {
            Parent::did_die(true);
            SAFE_DELETE(dying_event_);
        }
    }
}

void Player::move_to(const Point& new_diff, unsigned now)
{
    if (Parent::did_die() || dying_event_)
    {
        return;
    }

    if (new_diff.scalar() == 0)
    {
        return;
    }

    if (!move_event_)
    {
        move_event_ = new Game::Event::Move(    now,
                                                MsToCompleteMoving,
                                                Parent::point(),
                                                new_diff);
        Parent::point(Parent::point() + new_diff);
        return;
    }

    if (is_stopping_ && new_diff == move_event_->direction())
    {
        is_stopping_ = false;
    }

    if (!move_event_->can_reverse_by(new_diff))
    {
        return;
    }

    move_event_->reverse();
    Parent::point(Parent::point() + new_diff);

    if (is_stopping_)
    {
        is_stopping_ = false;
    }
}

void Player::will_die(unsigned now, unsigned ms_to_completion)
{
    ASSERT(!dying_event_);
    dying_event_ = new Event::Dying(now, ms_to_completion);
}

void Player::tick(unsigned now)
{
    if (dying_event_)
    {
        dying_event_->tick(now);
        return;
    }

    if (!move_event_)
    {
        return;
    }

    if (is_stopping_)
    {
        move_event_->tick_with_no_duration(now);
        return;
    }
    else if (will_stop_)
    {
        bool did_consume_all(false);
        move_event_->tick_until(now, ms_to_collision_, &did_consume_all);

        if (did_consume_all)
        {
            is_stopping_ = true;
        }

        return;
    }
    else
    {
        move_event_->tick(now);
        return;
    }
}

void Player::draw(const Image::Sprite& image)  const
{
    if (Parent::did_die())
    {
        return;
    }

    GameLib::Framework f = GameLib::Framework::instance();
    Size size = Size(f.width(), f.height());
    unsigned* vram = f.videoMemory();

    double alpha = dying_event_ ? dying_event_->completion_rate() : -1.0;

    if (!move_event_)
    {
        image.copy_alpha_blend( get_object_image_id(player_index_),
                                alpha,
                                Parent::point(),
                                size,
                                vram);
        return;
    }

    image.copy_alpha_blend( get_object_image_id(player_index_),
                            alpha,
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

void Player::stop_after(unsigned ms)
{
    will_stop_ = true;
    ms_to_collision_ = ms;
}

Piece Player::make_piece() const
{
    double unit_per_ms(0.0);
    double have_moved_unit(0.0);

    if (!move_event_)
    {
        return Piece(rect_, Parent::point(), Point(0, 0), unit_per_ms, have_moved_unit);
    }

    have_moved_unit = move_event_->completion_rate();

    if (!dying_event_ && !is_stopping_)
    {
        unit_per_ms = 1.0 / move_event_->ms_per_unit();
    }

    return Piece(   rect_,
                    move_event_->point(),
                    move_event_->direction(),
                    unit_per_ms,
                    have_moved_unit);
}

Point Player::current_point() const
{
    if (move_event_)
    {
        return move_event_->point();
    }
    return Parent::point();
}

bool Player::does_direction_open(const Player& other, unsigned ms) const
{
    if (!move_event_ || is_stopping_)
    {
        return false;
    }

    ms = ms + move_event_->ms_per_unit() / 2;

    Piece me = make_piece();
    me.have_moved_unit(me.have_moved_unit() + ms * me.unit_per_ms());
    Piece you = other.make_piece();

    return !me.does_overlap(you);
}

void Player::plant_a_bomb(  unsigned now,
                            Container::Bomb* bombs,
                            Map* map) const
{
    if (bombs->count(player_index_) >= max_bombs_)
    {
        return;
    }

    bombs->create_one(current_point(), power_, player_index_, now, map);
}

bool Player::does_dying_is_reserved() const { return !!dying_event_; }

} // namespace Object

} // namespace Game
