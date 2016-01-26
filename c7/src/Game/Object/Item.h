#ifndef BAKUDAN_GAME_OBJECT_ITEM_H_
#define BAKUDAN_GAME_OBJECT_ITEM_H_
#include "Game/Object/Parent.h"
#include "State.h"

namespace Game { class Map; }
namespace Game { namespace Object { class Player; } }
namespace Game { namespace Object { class Wall; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Object
{

class Item : public Parent
{
private:
    State::ObjectImage id_;
    int energy_;

public:
    Item(State::ObjectImage id, const Object::Wall& wall);
    virtual ~Item();
    virtual void draw(const Image::Sprite& image) const;
    virtual void draw(const Image::Sprite& image, const Map& map);
    virtual void give(Object::Player* player);
    virtual void tick(unsigned now);
};

} // namespace Object

} // namespace Game

#endif
