#ifndef BAKUDAN_GAME_CONTAINER_WALL_H_
#define BAKUDAN_GAME_CONTAINER_WALL_H_
#include <vector>

class Point;
namespace Game { class Map; }
namespace Game { namespace Object { class Wall; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Container
{

class Wall
{
private:
    std::vector< Game::Object::Wall* > walls_;

public:
    Wall(const Point& point1p, const Point& point2p, Map* map);
    ~Wall();
    void burn_one(const Point& point, unsigned now, unsigned ms_to_completion);
    void burn_wall_to_map(Map* map);
    void clean_up_all_garbage(Map* map);
    void draw(const Image::Sprite& image) const;
    void freeze_drawing_until_burn();
    void pause(unsigned now);
    void resume(unsigned now);
    void tick(unsigned now);
};

} // namespace Container

} // namespace Game

#endif
