#include "Game/Object/Parent.h"
#include "Point.h"

namespace Game
{

namespace Object
{

Parent::Parent()
: point_(0, 0), did_die_(false)
{}

Parent::Parent(const Point& point)
: point_(point), did_die_(false)
{}

Parent::~Parent() {}

const Point& Parent::point() const { return point_; }
void Parent::point(const Point& new_point) { point_ = new_point; }
bool Parent::did_die() const { return did_die_; }
void Parent::did_die(bool new_value) { did_die_ = new_value; }

} // namespace Object

} // namespace Game
