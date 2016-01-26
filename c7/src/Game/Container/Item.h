#ifndef BAKUDAN_GAME_CONTAINER_ITEM_H_
#define BAKUDAN_GAME_CONTAINER_ITEM_H_
#include <utility>
#include <vector>

class Point;
namespace Game { class Map; }
namespace Game { namespace Container { class Wall; } }
namespace Game { namespace Object { class Item; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Container
{

class Item
{
private:
    std::vector< Object::Item* > items_;

public:
    Item(int bomb_count, int power_count, const Container::Wall& walls);
    ~Item();
    void clean_up_all_garbage();
    void draw(const Image::Sprite& image, const Map& map) const;
    std::pair< bool, Object::Item* > get_item(const Point& point);
};

} // namespace Container

} // namespace Game

#endif
