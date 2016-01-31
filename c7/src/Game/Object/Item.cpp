#include "Game/Object/Item.h"
#include "GameLib/Framework.h"
#include "Game/Map.h"
#include "Game/Object/Player.h"
#include "Game/Object/Wall.h"
#include "Image/Sprite.h"
#include "Size.h"
#include "State.h"

namespace Game
{

namespace Object
{

Item::Item(State::ObjectImage id, const Object::Wall& wall)
: Parent(wall.point()), id_(id), energy_(1)
{}

Item::~Item() {}

void Item::draw(const Image::Sprite& image) const {}

void Item::draw(const Image::Sprite& image, const Map& map)
{
    if (map.is_wall(Parent::point()) && !map.is_burning_wall(Parent::point()))
    {
        return;
    }

    image.copy(id_, Parent::point());
}

void Item::give(Object::Player* player)
{
    if (id_ == State::OBJECT_IMAGE_BOMB_ITEM)
    {
        player->max_bombs(player->max_bombs() + energy_);
        energy_ = 0;
        Parent::did_die(true);
    }

    if (id_ == State::OBJECT_IMAGE_SOTRM_ITEM)
    {
        player->power(player->power() + energy_);
        energy_ = 0;
        Parent::did_die(true);
    }
}

void Item::tick(unsigned) {}

} // namespace Object

} // namespace Game
