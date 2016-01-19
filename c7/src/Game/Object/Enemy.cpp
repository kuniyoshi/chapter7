#include "Game/Object/Enemy.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "Game/Ai/RuleBase.h"
#include "Game/Event/Dying.h"
#include "Game/Event/Eat.h"
#include "Game/Event/Move.h"
#include "Game/Map.h"
#include "Game/Object/Player.h"
#include "Image/Sprite.h"
#include "Iterator/Image.h"
#include "Piece.h"
#include "Rect.h"
#include "Size.h"

namespace Game
{

namespace Object
{

namespace
{

const unsigned MsToCompleteEating   = 1000;
const unsigned MsToCompleteMoving   = 1000;

} // namespace

void Enemy::place_enemies(  const Game::Map& map,
                            int group_points_size,
                            const Point* group_points,
                            int enemy_points_size,
                            Point* enemy_points)
{
    int placable_points_size = 0;
    Iterator::Image iterator(   Point(0, 0),
                                Point(map.width() - 1, map.height() - 1),
                                Size(map.width(), map.height()));

    while (iterator.has_next())
    {
        if (!map.can_not_invade(iterator.unbiased_x(), iterator.unbiased_y()))
        {
            ++placable_points_size;
        }

        ++iterator;
    }

    iterator.reset();

    ASSERT(placable_points_size > enemy_points_size);

    Point* placable_points = new Point[placable_points_size];
    int* distances = new int[placable_points_size];
    int place_index = 0;

    while (iterator.has_next())
    {
        if (!map.can_not_invade(iterator.unbiased_x(), iterator.unbiased_y()))
        {
            placable_points[place_index].set_xy(    iterator.unbiased_x(),
                                                    iterator.unbiased_y());

            int min_distance = placable_points[place_index].distance(group_points[0]);

            for (int i = 1; i < group_points_size; ++i)
            {
                int distance_candidate = placable_points[place_index].distance(group_points[i]);

                if (distance_candidate < min_distance)
                {
                    min_distance = distance_candidate;
                }
            }

            distances[place_index] = min_distance;
            ++place_index;
        }

        ++iterator;
    }

    int max_distance = 0;

    for (int i = 0; i < placable_points_size; ++i)
    {
        if (distances[i] > max_distance)
        {
            max_distance = distances[i];
        }
    }

    for (int i = 0; i < placable_points_size; ++i)
    {
        distances[i] = max_distance + 1 - distances[i];
    }

    int sum_distance = 0;

    for (int i = 0; i < placable_points_size; ++i)
    {
        sum_distance = sum_distance + distances[i];
    }

    GameLib::Framework f = GameLib::Framework::instance();

    for (int i = 0; i < enemy_points_size; ++i)
    {
        int rand_value = f.getRandom(sum_distance);
        int cumsum = 0;
        int j = 0;

        for (j = 0; j < placable_points_size; ++j)
        {
            cumsum = cumsum + distances[j];

            if (cumsum > rand_value)
            {
                break;
            }
        }

        enemy_points[i].set_xy( placable_points[j].x(),
                                placable_points[j].y());

        sum_distance = sum_distance - distances[j];
        distances[j] = 0;
    }

    SAFE_DELETE_ARRAY(placable_points);
    SAFE_DELETE_ARRAY(distances);
}

void Enemy::setup_enemies(  int enemy_points_size,
                            const Point* enemy_points,
                            const Image::Sprite& image,
                            Game::Object::Enemy* enemies)
{
    Rect< double > rect;
    image.set_inner_area_of(State::OBJECT_IMAGE_ENEMY, &rect);

    for (int i = 0; i < enemy_points_size; ++i)
    {
        enemies[i].Parent::point(enemy_points[i]);
        enemies[i].rect_ = rect;
        ASSERT(!enemies[i].ai_);
        enemies[i].ai_ = new Game::Ai::RuleBase(25, 25, 25, 25, 0);
    }
}

Enemy::Enemy()
:   is_stopping_(false), will_stop_(false), ms_to_collision_(0),
    ai_(0), dying_event_(0), eat_event_(0), move_event_(0),
    rect_()
{}

Enemy::~Enemy()
{
    SAFE_DELETE(ai_);
    SAFE_DELETE(dying_event_);
    SAFE_DELETE(eat_event_);
    SAFE_DELETE(move_event_);
}

void Enemy::draw(const Image::Sprite& image) const
{
    if (Parent::did_die())
    {
        return;
    }

    GameLib::Framework f = GameLib::Framework::instance();
    Size size(f.width(), f.height());
    unsigned* vram = f.videoMemory();

    double alpha = dying_event_ ? dying_event_->completion_rate() : -1.0;

    if (!move_event_)
    {
        image.copy_alpha_blend( State::OBJECT_IMAGE_ENEMY,
                                alpha,
                                Parent::point(),
                                size,
                                vram);
        return;
    }

    image.copy_alpha_blend( State::OBJECT_IMAGE_ENEMY,
                            alpha,
                            *move_event_,
                            size,
                            vram);
}

Point Enemy::current_point() const
{
    return move_event_ ? move_event_->point() : Parent::point();
}

void Enemy::eat(unsigned now, Game::Object::Player* player)
{
    ASSERT(!Parent::did_die());

    if (!eat_event_)
    {
        eat_event_ = new Game::Event::Eat(now, MsToCompleteEating);
        player->will_die(now, MsToCompleteEating);
    }
}

Piece Enemy::make_piece() const
{
    double unit_per_ms = 0.0;
    double have_moved_unit = 0.0;

    if (!move_event_)
    {
        return Piece(   rect_,
                        Parent::point(),
                        Point(0, 0),
                        unit_per_ms,
                        have_moved_unit);
    }

    have_moved_unit = move_event_->completion_rate();

    if (!is_stopping_)
    {
        unit_per_ms = 1.0 / move_event_->ms_per_unit();
    }

    return Piece(   rect_,
                    move_event_->point(),
                    move_event_->direction(),
                    unit_per_ms,
                    have_moved_unit);
}

#ifndef NDEBUG
void Enemy::move_to(const Point& direction, unsigned now)
{
    if (Parent::did_die() || dying_event_)
    {
        return;
    }

    if (direction.scalar() == 0)
    {
        return;
    }

    if (!move_event_)
    {
        move_event_ = new Game::Event::Move(    now,
                                                MsToCompleteMoving,
                                                Parent::point(),
                                                direction);
        Parent::point(Parent::point() + direction);
        return;
    }

    if (is_stopping_ && direction == move_event_->direction())
    {
        is_stopping_ = false;
    }

    if (!move_event_->can_reverse_by(direction))
    {
        return;
    }

    move_event_->reverse();
    Parent::point(Parent::point() + direction);

    if (is_stopping_)
    {
        is_stopping_ = false;
    }
}
#endif

void Enemy::pause(unsigned now)
{
    if (eat_event_)
    {
        eat_event_->pause(now);
    }

    if (move_event_)
    {
        move_event_->pause(now);
    }
}

void Enemy::prepare()
{
    // clear volatility condition
    {
        will_stop_ = false;
        ms_to_collision_ = 0;
    }

    // complete event
    {
        if (dying_event_ && dying_event_->did_complete())
        {
            SAFE_DELETE(dying_event_);
            SAFE_DELETE(eat_event_);
            SAFE_DELETE(move_event_);
            Parent::did_die(true);
        }

        if (eat_event_ && eat_event_->did_complete())
        {
            SAFE_DELETE(eat_event_);
        }

        if (move_event_ && move_event_->did_complete())
        {
            SAFE_DELETE(move_event_);
        }
    }
}

void Enemy::resume(unsigned now)
{
    if (eat_event_)
    {
        eat_event_->resume(now);
    }

    if (move_event_)
    {
        move_event_->resume(now);
    }
}

void Enemy::reverse()
{
    if (!move_event_)
    {
        return;
    }

    Parent::point(move_event_->point());
    move_event_->reverse();
}

void Enemy::set_direction(  const Map& map,
                            int enemies_size,
                            const Enemy* enemies,
                            int self_index,
                            unsigned now)
{
    if (eat_event_ || dying_event_)
    {
        return;
    }

    if (is_stopping_ && ai_->can_start_moving(  *this,
                                                enemies_size,
                                                enemies,
                                                self_index))
    {
        is_stopping_ = false;
        return;
    }

    if (move_event_ && ai_->can_reverse_direction(  *this,
                                                    enemies_size,
                                                    enemies,
                                                    self_index))
    {
        reverse();
        return;
    }

    if (!move_event_)
    {
        Point direction(ai_->select_direction(  *this,
                                                map,
                                                enemies_size,
                                                enemies,
                                                self_index));
        move_event_ = new Event::Move(  now,
                                        MsToCompleteMoving,
                                        Parent::point(),
                                        direction);
        Parent::point(Parent::point() + direction);
    }
}

void Enemy::set_direction_at_collision()
{
    if (move_event_ && !is_stopping_)
    {
        reverse();
    }
}

void Enemy::stop_after(unsigned ms_to_collision)
{
    will_stop_ = true;
    ms_to_collision_ = ms_to_collision;
}

void Enemy::tick(unsigned now)
{
    if (Parent::did_die())
    {
        return;
    }

    if (dying_event_)
    {
        dying_event_->tick(now);

        // ignore eat event, it will be deleted at died

        if (move_event_)
        {
            move_event_->tick_with_no_duration(now);
        }

        return;
    }

    if (eat_event_)
    {
        eat_event_->tick(now);

        if (move_event_)
        {
            move_event_->tick_with_no_duration(now);
        }

        return;
    }

    if (move_event_)
    {
        move_event_->tick(now);
    }
}

void Enemy::will_die(unsigned now, unsigned ms_to_completion)
{
    SAFE_DELETE(eat_event_);
    ASSERT(!dying_event_);

    dying_event_ = new Game::Event::Dying(now, ms_to_completion);
}

} // namespace Object

} // namespace Game
