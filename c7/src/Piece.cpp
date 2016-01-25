#include "Piece.h"
#include "Point.h"
#include "Rect.h"

Piece::Piece(   const Rect< double >& rect,
                const Point& point,
                const Point& direction,
                double unit_per_ms,
                double have_moved_unit)
:   rect_(rect), point_(point), direction_(direction),
    unit_per_ms_(unit_per_ms), have_moved_unit_(have_moved_unit)
{}

Piece::Piece(const Piece& base)
:   rect_(base.rect_), point_(base.point_), direction_(base.direction_),
    unit_per_ms_(base.unit_per_ms_), have_moved_unit_(base.have_moved_unit_)
{}

Piece::~Piece() {}

const Rect< double >& Piece::rect() const { return rect_; }
double Piece::left() const { return rect_.left(); }
double Piece::right() const { return rect_.right(); }
double Piece::top() const { return rect_.top(); }
double Piece::bottom() const { return rect_.bottom(); }
const Point& Piece::point() const { return point_; }
const Point& Piece::direction() const { return direction_; }
double Piece::unit_per_ms() const { return unit_per_ms_; }
double Piece::x_unit_per_ms() const { return direction_.x() * unit_per_ms_; }
double Piece::y_unit_per_ms() const { return direction_.y() * unit_per_ms_; }
double Piece::have_moved_unit() const { return have_moved_unit_; }
void Piece::have_moved_unit(double new_value) { have_moved_unit_ = new_value; }

double Piece::get_current_x_offset() const
{
    return direction_.x() * have_moved_unit_;
}

double Piece::get_current_y_offset() const
{
    return direction_.y() * have_moved_unit_;
}

double Piece::get_x_difference_to(const Piece& destination) const
{
    if (destination.point_.x() == point_.x())
    {
        return 0.0;
    }

    double difference(0.0);
    double source_offset(get_current_x_offset());
    double destination_offset(destination.get_current_x_offset());

    if (destination.point_.x() > point_.x())
    {
        source_offset = source_offset + rect_.right();
        destination_offset = destination_offset + destination.rect_.left();
    }
    else
    {
        source_offset = source_offset + rect_.left();
        destination_offset = destination_offset + destination.rect_.right();
    }

    difference
    = (destination.point_.x() + destination_offset) - (point_.x() + source_offset);

    return difference;
}

double Piece::get_y_difference_to(const Piece& destination) const
{
    if (destination.point_.y() == point_.y())
    {
        return 0.0;
    }

    double difference(0.0);
    double source_offset(get_current_y_offset());
    double destination_offset(destination.get_current_y_offset());

    if (destination.point_.y() > point_.y())
    {
        source_offset = source_offset + rect_.bottom();
        destination_offset = destination_offset + destination.rect_.top();
    }
    else
    {
        source_offset = source_offset + rect_.top();
        destination_offset = destination_offset + destination.rect_.bottom();
    }

    difference
    = (destination.point_.y() + destination_offset) - (point_.y() + source_offset);

    return difference;
}

bool Piece::does_overlap(const Piece& other) const
{
    Point point_diff = other.point_ - point_;
    bool is_x_same(point_diff.x() == 0);
    bool is_y_same(point_diff.y() == 0);

    double this_x_offset(point_.x() + get_current_x_offset());
    double this_left = this_x_offset + rect_.left();
    double this_right = this_x_offset + rect_.right();
    double other_x_offset(other.point_.x() + other.get_current_x_offset());
    double other_left = other_x_offset + other.rect_.left();
    double other_right = other_x_offset + other.rect_.right();

    bool does_x_overlap = point_.x() < other.point_.x()
        && this_right > other_left;
    does_x_overlap = does_x_overlap
        || (point_.x() > other.point_.x() && this_left < other_right);

    if (is_y_same)
    {
        return does_x_overlap;
    }

    double this_y_offset(point_.y() + get_current_y_offset());
    double this_top = this_y_offset + rect_.top();
    double this_bottom = this_y_offset + rect_.bottom();
    double other_y_offset(other.point_.y() + other.get_current_y_offset());
    double other_top = other_y_offset + other.rect_.top();
    double other_bottom = other_y_offset + other.rect_.bottom();

    bool does_y_overlap = point_.y() < other.point_.y()
        && this_bottom > other_top;
    does_y_overlap = does_y_overlap
        || (point_.y() > other.point_.y() && this_top < other_bottom);

    if (is_x_same)
    {
        return does_y_overlap;
    }

    return does_x_overlap && does_y_overlap;
}

Rect< double > Piece::make_rect() const
{
    double this_x_offset = point_.x() + get_current_x_offset();
    double this_y_offset = point_.y() + get_current_y_offset();
    return Rect< double >(  this_x_offset + rect_.left(),
                            this_x_offset + rect_.right(),
                            this_y_offset + rect_.top(),
                            this_y_offset + rect_.bottom());
}
