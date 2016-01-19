#ifndef BAKUDAN_GAME_OBJECT_ENEMY_H
#define BAKUDAN_GAME_OBJECT_ENEMY_H
#include "Game/Object/Parent.h"
#include "Rect.h"

class Piece;
class Point;
namespace Game { class Map; }
namespace Game { namespace Ai { class RuleBase; } }
namespace Game { namespace Event { class Dying; } }
namespace Game { namespace Event { class Eat; } }
namespace Game { namespace Event { class Move; } }
namespace Game { namespace Object { class Player; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Object
{

class Enemy : public Parent
{
public:
    static void place_enemies(  const Map& map,
                                int group_points_size,
                                const Point* group_points,
                                int enemy_points_size,
                                Point* enemy_points);
    static void setup_enemies(  int enemy_points_size,
                                const Point* enemy_points,
                                const Image::Sprite& image,
                                Enemy* enemies);

private:
    bool is_stopping_;
    bool will_stop_;
    unsigned ms_to_collision_;
    Ai::RuleBase* ai_;
    Event::Dying* dying_event_;
    Event::Eat* eat_event_;
    Event::Move* move_event_;
    Rect< double > rect_;

public:
    Enemy();
    virtual ~Enemy();
    virtual void draw(const Image::Sprite& image) const;
    virtual Point current_point() const;
    virtual void eat(unsigned now, Player* player);
    virtual Piece make_piece() const;
#ifndef NDEBUG
    virtual void move_to(const Point& direction, unsigned now);
#endif
    virtual void pause(unsigned now);
    virtual void prepare();
    virtual void resume(unsigned now);
    virtual void reverse();
    virtual void set_direction( const Map& map,
                                int enemies_size,
                                const Enemy* enemies,
                                int self_index,
                                unsigned now);
    virtual void set_direction_at_collision();
    virtual void stop_after(unsigned ms_to_collision);
    virtual void tick(unsigned now);
    virtual void will_die(unsigned now, unsigned ms_to_completion);
};

} // namespace Object

} // namespace Game

#endif
