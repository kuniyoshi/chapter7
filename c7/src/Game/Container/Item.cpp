#include "Game/Container/Item.h"
#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include "GameLib/Framework.h"
#include "Game/Container/Wall.h"
#include "Game/Map.h"
#include "Game/Object/Item.h"
#include "Point.h"
#include "State.h"

namespace Game
{

namespace Container
{

Item::Item(int bomb_count, int power_count, const Container::Wall& walls)
: items_(std::vector< Object::Item* >())
{
    int items_size = bomb_count + power_count;
    ASSERT(items_size < walls.size());

    GameLib::Framework f = GameLib::Framework::instance();

    std::vector< int > rand_values;
    rand_values.reserve(walls.size());

    for (int i = 0; i < walls.size(); ++i)
    {
        rand_values.push_back(i);
    }

    std::shuffle(rand_values.begin(), rand_values.end(), std::mt19937());

    std::vector< int >::iterator iterator = rand_values.begin();

    State::ObjectImage object_id = State::OBJECT_IMAGE_BOMB_ITEM;

    for (int i = 0; i < bomb_count; ++i)
    {
        items_.push_back(new Object::Item(object_id, *(walls.at(*iterator))));
        ++iterator;
    }

    object_id = State::OBJECT_IMAGE_SOTRM_ITEM;

    for (int i = 0; i < power_count; ++i)
    {
        items_.push_back(new Object::Item(object_id, *(walls.at(*iterator))));
        ++iterator;
    }
}

Item::~Item()
{
    std::vector< Object::Item* >::iterator iterator = items_.begin();

    for (; iterator != items_.end(); ++iterator)
    {
        SAFE_DELETE(*iterator);
    }

    items_.clear();
}

void Item::clean_up_all_garbage()
{
    std::vector< Object::Item* >::iterator iterator = items_.begin();

    for (; iterator != items_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        if ((*iterator)->did_die())
        {
            SAFE_DELETE(*iterator);
        }
    }
}

void Item::draw(const Image::Sprite& image, const Map& map) const
{
    std::vector< Object::Item* >::const_iterator iterator = items_.begin();

    for (; iterator != items_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        (*iterator)->draw(image, map);
    }
}

std::pair< bool, Object::Item* > Item::get_item(const Point& point)
{
    std::vector< Object::Item* >::iterator iterator = items_.begin();

    for (; iterator != items_.end(); ++iterator)
    {
        if (!(*iterator))
        {
            continue;
        }

        if ((*iterator)->point() == point)
        {
            return std::pair< bool, Object::Item* >(true, *iterator);
        }
    }

    return std::pair< bool, Object::Item* >(false, 0);
}

} // namespace Container

} // namespace Game
