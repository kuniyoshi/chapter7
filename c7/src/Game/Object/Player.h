#ifndef BAKUDAN_GAME_OBJECT_PLAYER_H
#define BAKUDAN_GAME_OBJECT_PLAYER_H
#include "Game/Object/Parent.h"
#include "Rect.h"

class Piece;
class Point;
namespace Game { class Map; }
namespace Game { namespace Container { class Bomb; } }
namespace Game { namespace Container { class Item; } }
namespace Game { namespace Event { class Dying; } }
namespace Game { namespace Event { class Move; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Object
{

class Player : public Parent
{
public:
    static const int MaxBombs;

private:
    int player_index_;
    Event::Dying* dying_event_;
    Event::Move* move_event_;
    Rect< double > rect_;
    unsigned ms_to_collision_;
    bool will_stop_;
    bool is_stopping_;
    int power_;
    int max_bombs_;

public:
    Player(int index, const Point& point, const Image::Sprite& image);
    virtual ~Player();
    virtual int player_index() const;
    virtual void ms_to_collision(unsigned new_value);
    virtual bool is_stopping() const;
    virtual int power() const;
    virtual void power(int new_value);
    virtual int max_bombs() const;
    virtual void max_bombs(int new_value);
    virtual void prepare();
    virtual void move_to(const Point& new_point, unsigned now);
    virtual void will_die(unsigned now, unsigned ms_to_completion);
    virtual void tick(unsigned now);
    virtual void draw(const Image::Sprite& image) const;
    virtual void pause(unsigned now);
    virtual void resume(unsigned now);
    virtual void stop_after(unsigned ms);
    virtual Piece make_piece() const;
    virtual Point current_point() const;
    virtual bool does_direction_open(const Player& other, unsigned ms) const;
    virtual void plant_a_bomb(  unsigned now,
                                Container::Bomb* bombs,
                                Map* map) const;
    virtual bool does_dying_is_reserved() const;
    virtual void gain_item(Container::Item* items);
};

} // namespace Object

} // namespace Game

#endif
