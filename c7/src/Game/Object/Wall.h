#ifndef BAKUDAN_GAME_OBJECT_WALL_H_
#define BAKUDAN_GAME_OBJECT_WALL_H_
#include "Game/Object/Parent.h"

class Point;
namespace Game { namespace Event { class Burn; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Object
{

class Wall : public Parent
{
private:
    Event::Burn* burn_event_;

public:
    Wall(const Point& point);
    ~Wall();
    void draw(const Image::Sprite& image) const;
    bool is_burning() const;
    void pause(unsigned now);
    void resume(unsigned now);
    void tick(unsigned now);
    void will_burn(unsigned now, unsigned ms_to_completion);
};

} // namespace Object

} // namespace Game

#endif
