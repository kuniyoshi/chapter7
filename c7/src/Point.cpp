#include "Point.h"

Point::Point() {}
Point::Point(int x, int y) : x_(x), y_(y) { }

bool Point::operator==(const Point& other) const
{
	return x_ == other.x() && y_ == other.y();
}
bool Point::operator!=(const Point& other) const
{
	return x_ != other.x() || y_ != other.y();
}
Point Point::operator+(const Point& operand) const
{
	return Point(x_ + operand.x_, y_ + operand.y_);
}
void Point::operator+=(const Point& operand)
{
	x_ += operand.x_;
	y_ += operand.y_;
}

int Point::x() const { return x_; }
int Point::y() const { return y_; }
void Point::set_xy(int x, int y)
{
	x_ = x;
	y_ = y;
}

bool Point::is_in(const Point& left_top, const Point& right_bottom) const
{
	return x_ >= left_top.x()
		&& x_ <= right_bottom.x()
		&& y_ >= left_top.y()
		&& y_ <= right_bottom.y();
}
