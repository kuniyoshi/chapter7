#include "Game/Container/Wall.h"
#include <vector>
#include "GameLib/Framework.h"
#include "Game/Map.h"
#include "Game/Object/Wall.h"
#include "Iterator/Image.h"
#include "Point.h"
#include "Size.h"
#include "State.h"

namespace Game
{

namespace Container
{

namespace
{

const int WallPercent           = 40;
const int DistanceToKeepArea    = 3;

} // namespace -

Wall::Wall(const Point& point1p, const Point& point2p, Map* map)
: walls_(std::vector< Object::Wall* >())
{
    GameLib::Framework f = GameLib::Framework::instance();

    Iterator::Image image_iterator( Point(0, 0),
                                    Point(map->width() - 1, map->height() - 1),
                                    Size(map->width(), map->height()));

    int wall_count = 0;

    for (; image_iterator.has_next(); ++image_iterator)
    {
        Point p(image_iterator.unbiased_x(), image_iterator.unbiased_y());

        if (p.distance(point1p) < DistanceToKeepArea)
        {
            continue;
        }

        if (p.distance(point2p) < DistanceToKeepArea)
        {
            continue;
        }

        if (map->can_not_invade(p))
        {
            continue;
        }

        if (f.getRandom(100) < WallPercent)
        {
            map->place(State::OBJECT_IMAGE_WALL, p);
            ++wall_count;
        }
    }

    walls_.reserve(wall_count);

    image_iterator.reset();

    for (; image_iterator.has_next(); ++image_iterator)
    {
        Point p(image_iterator.unbiased_x(), image_iterator.unbiased_y());

        if (map->is_wall(p))
        {
            walls_.push_back(new Object::Wall(p));
        }
    }
}

Wall::~Wall()
{
    std::vector< Object::Wall* >::iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        SAFE_DELETE(*iterator);
    }

    walls_.clear();
}

const Object::Wall* Wall::at(int index) const { return walls_.at(index); }

void Wall::burn_one(const Point& point, unsigned now, unsigned ms_to_completion)
{
    std::vector< Object::Wall* >::iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        if ((*iterator)->is_burning())
        {
            continue;
        }

        if ((*iterator)->point() == point)
        {
            (*iterator)->will_burn(now, ms_to_completion);
            break;
        }
    }
}

void Wall::burn_wall_to_map(Map* map)
{
    std::vector< Object::Wall* >::iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        if ((*iterator)->is_burning())
        {
            map->place(State::OBJECT_IMAGE_BURNING_WALL, (*iterator)->point());
        }
    }
}

void Wall::clean_up_all_garbage(Map* map)
{
    std::vector< Object::Wall* >::iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        if ((*iterator)->did_die())
        {
            map->clear((*iterator)->point());
            SAFE_DELETE(*iterator);
        }
    }
}

void Wall::draw(const Image::Sprite& image) const
{
    std::vector< Object::Wall* >::const_iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->draw(image);
    }
}

void Wall::pause(unsigned now)
{
    std::vector< Object::Wall* >::iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->pause(now);
    }
}

void Wall::resume(unsigned now)
{
    std::vector< Object::Wall* >::iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->resume(now);
    }
}

int Wall::size() const { return walls_.size(); }

void Wall::tick(unsigned now)
{
    std::vector< Object::Wall* >::iterator iterator = walls_.begin();

    for (; iterator != walls_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->tick(now);
    }
}

} // namespace Container

} // namespace Game
