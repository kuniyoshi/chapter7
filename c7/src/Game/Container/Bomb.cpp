#include "Game/Container/Bomb.h"
#include <utility>
#include <vector>
#include "GameLib/GameLib.h"
#include "Game/Container/Wall.h"
#include "Game/Map.h"
#include "Game/Object/Bomb.h"
#include "Game/Object/Enemy.h"
#include "Game/Object/Player.h"
#include "Image/Sprite.h"
#include "Constants.h"
#include "Piece.h"
#include "Rect.h"

namespace Game
{

namespace Container
{

namespace
{

const unsigned MsToCompleteBurning      = 1000;
const unsigned MsToCompleteBurningWall  = 500;

} // namespace -

Bomb::Bomb(int max_count, const Image::Sprite& image)
:   bombs_(std::vector< Object::Bomb* >()),
    central_(), horizontal_(), vertical_()
{
    bombs_.reserve(max_count);
    image.set_inner_area_of(State::OBJECT_IMAGE_BOMB, &central_);
    image.set_inner_area_of(State::OBJECT_IMAGE_HORIZONTAL_STORM, &horizontal_);
    image.set_inner_area_of(State::OBJECT_IMAGE_VERTICAL_STORM, &vertical_);
}

Bomb::~Bomb()
{
    std::vector< Object::Bomb* >::iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        SAFE_DELETE(*iterator);
    }

    bombs_.clear();
}

void Bomb::burn_out_walls_if_explosion_reaches( unsigned now,
                                                const Map& map,
                                                Container::Wall* walls) const
{
    std::vector< Object::Bomb* >::const_iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator) || !(*iterator)->is_exploding())
        {
            continue;
        }

        for (int i = 0; i < Constants::DirectionNameSize; ++i)
        {
            Constants::DirectionName id
            = static_cast< Constants::DirectionName >(i);
            Point point = (*iterator)->max_point(id);

            if (map.is_wall(point))
            {
                walls->burn_one(point, now, MsToCompleteBurningWall);
            }
        }
    }
}

int Bomb::count(int player_index) const
{
    int count = 0;
    std::vector< Object::Bomb* >::const_iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        if ((*iterator)->is_owner_same_as(player_index))
        {
            ++count;
        }
    }

    return count;
}

void Bomb::chain_explosion(unsigned now)
{
    std::vector< Object::Bomb* >::const_iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator) || !(*iterator)->is_exploding())
        {
            continue;
        }

        std::vector< Object::Bomb* >::iterator i2 = bombs_.begin();

        for (; i2 != bombs_.end(); ++i2)
        {
            if (!(*i2) || i2 == iterator || (*i2)->is_exploding())
            {
                continue;
            }

            if ((*iterator)->does_overlap((*i2)->central()))
            {
                (*i2)->will_explode();
            }
        }
    }
}

void Bomb::clean_up_all_garbage(Map* map)
{
    std::vector< Object::Bomb* >::iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        if ((*iterator)->did_complete_explosion())
        {
            map->clear((*iterator)->point());
            SAFE_DELETE(*iterator);
        }
    }
}

void Bomb::create_one(  const Point& destination,
                        int power,
                        int player_index,
                        unsigned now,
                        Map* map)
{
    if (map->can_not_invade(destination))
    {
        return;
    }

    std::vector< Object::Bomb* >::iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (*iterator)
        {
            continue;
        }

        *iterator = new Object::Bomb(destination, power, player_index, now);
        (*iterator)->setup(central_, horizontal_, vertical_);

        map->place(State::OBJECT_IMAGE_BOMB, (*iterator)->point());

        return;
    }

    HALT("No enough bombs_.size() to create a new bomb.");
}

void Bomb::draw(const Image::Sprite& image) const
{
    std::vector< Object::Bomb* >::const_iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->draw(image);
    }
}

void Bomb::kill_enemies_if_in_explosion(    unsigned now,
                                            int enemies_size,
                                            Object::Enemy* enemies) const
{
    std::vector< Object::Bomb* >::const_iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator) || !(*iterator)->is_exploding())
        {
            continue;
        }

        for (int i = 0; i < enemies_size; ++i)
        {
            if (enemies[i].did_die() || enemies[i].does_dying_is_reserved())
            {
                continue;
            }

            Piece piece = enemies[i].make_piece();

            if ((*iterator)->does_overlap(piece.make_rect()))
            {
                enemies[i].will_die(now, MsToCompleteBurning);
            }
        }
    }
}

void Bomb::kill_player_if_in_explosion( unsigned now,
                                        Object::Player* player) const
{
    if (player->did_die() || player->does_dying_is_reserved())
    {
        return;
    }

    Piece piece = player->make_piece();

    std::vector< Object::Bomb* >::const_iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator) || !(*iterator)->is_exploding())
        {
            continue;
        }

        if ((*iterator)->does_overlap(piece.make_rect()))
        {
            player->will_die(now, MsToCompleteBurning);
            return;
        }
    }
}

void Bomb::pause(unsigned now)
{
    std::vector< Object::Bomb* >::iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->pause(now);
    }
}

void Bomb::resume(unsigned now)
{
    std::vector< Object::Bomb* >::iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->resume(now);
    }
}

void Bomb::tick(unsigned now, const Map& map)
{
    std::vector< Object::Bomb* >::iterator iterator = bombs_.begin();

    for (; iterator != bombs_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->tick(now, map);
    }
}

} // namespace Container

} // namespace Game
