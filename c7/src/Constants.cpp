#include "Constants.h"
#include "Point.h"

Constants::Constants() {}
Constants::~Constants() {}

namespace
{

const Point Directions[] = {    Point(-1, 0),
                                Point(0, -1),
                                Point(0, -1),
                                Point(0, 1)};

} // namespace -

const Point& Constants::direction(DirectionName id)
{
    return Directions[static_cast< int >(id)];
}
