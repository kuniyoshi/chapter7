#ifndef BAKUDAN_POINT_H_
#define BAKUDAN_POINT_H_

class Point
{
private:
	int x_;
	int y_;

public:
	Point();
	Point(int x, int y);
	Point(const Point& base, int x, int y);
	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;
	Point operator+(const Point& operand) const;
	Point operator-(const Point& operand) const;
	void operator+=(const Point& operand);
	int x() const;
	int y() const;
	void set_xy(int x, int y);
	bool is_in(const Point& left_top, const Point& right_bottom) const;
	int scalar() const;
};

#endif
