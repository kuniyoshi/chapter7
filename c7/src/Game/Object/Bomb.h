#ifndef BAKUDAN_GAME_OBJECT_BOMB_H_
#define BAKUDAN_GAME_OBJECT_BOMB_H_
#include <vector>
#include "Constants.h"
#include "Game/Event/Explode.h"
#include "Game/Object/Parent.h"
#include "Rect.h"

class Piece;
class Point;
namespace Game { class Map; }
namespace Image { class Sprite; }

namespace Game
{

namespace Object
{

class Bomb : public Parent
{
private:
    Event::Explode* explode_event_;
    Rect< double > central_;
    Rect< double > horizontal_;
    Rect< double > vertical_;
    bool will_explode_;
    int owner_id_;
    std::vector< Point* > pieces_;

public:
    Bomb(const Point& destination, int power, int owner_id, unsigned now);
    ~Bomb();
    void setup( const Rect< double >& central,
                const Rect< double >& horizontal,
                const Rect< double >& vertical);
    Rect< double > central() const;
    void will_explode();

    bool did_complete_explosion() const;
    bool does_overlap(const Rect< double >& rect) const;
    void draw(const Image::Sprite& image) const;
    bool is_exploding() const;
    bool is_owner_same_as(int id) const;
    Point max_point(Constants::DirectionName id) const;
    void pause(unsigned now);
    void resume(unsigned now);
    void tick(unsigned now);
    void tick(unsigned now, const Map& map);
};

} // namespace Object

} // namespace Game

#endif
