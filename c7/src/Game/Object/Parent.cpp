#include "Game/Object/Parent.h"
#include "Point.h"

namespace Game
{

namespace Object
{

Parent::Parent() : point_(0, 0) {}
Parent::Parent(const Point& point) : point_(point) {}
Parent::~Parent() {}

const Point& Parent::point() const { return point_; }
void Parent::point(const Point& new_point) { point_ = new_point; }

} // namespace Object

} // namespace Game
