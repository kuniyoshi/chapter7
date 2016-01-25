#ifndef BAKUDAN_GAME_EVENT_EXPLODE
#define BAKUDAN_GAME_EVENT_EXPLODE
#include <utility>
#include <vector>
#include "Constants.h"
#include "Game/Event/Parent.h"

class Piece;
class Point;
namespace Game { class Map; }

namespace Game
{

namespace Event
{

class Explode : public Parent
{
private:
    int power_;
    std::vector< std::pair< bool, double > > max_lengths_;
    std::vector< unsigned > ms_statuses_;
    unsigned duration_;

public:
    Explode(unsigned now, int power, unsigned ms_to_start_explosion);
    ~Explode();
    int power() const;
    bool did_complete() const;
    void explode();
    double get_alpha() const;
    bool is_exploding() const;
    double length(Constants::DirectionName id) const;
    std::pair< bool, double > stopped_length(Constants::DirectionName id) const;
    void tick(unsigned now);
    void tick(unsigned now, const Point& point, const Map& map);
};

} // namespace Event

} // namespace Game

#endif
