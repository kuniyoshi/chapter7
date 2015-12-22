#pragma once

class Point
{
private:
	int x_, y_;

public:
	Point();
	Point(int x, int y);
	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;
	int x() const;
	int y() const;
	void set_xy(int x, int y);
	bool is_in(const Point& left_top, const Point& right_bottom) const;
};
