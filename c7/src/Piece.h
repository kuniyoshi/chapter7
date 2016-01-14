#ifndef BAKUDAN_PIECE_H_
#define BAKUDAN_PIECE_H_
#include "Point.h"
#include "Rect.h"

class Piece
{
private:
	Rect< double > rect_;
	Point point_;
	Point direction_;
	double unit_per_ms_;
	double have_moved_unit_;

public:
	Piece(	const Rect< double >& rect,
			const Point& point,
			const Point& direction,
			double unit_per_ms,
			double have_moved_unit);
	Piece(const Piece& base);
	~Piece();

	const Rect< double >& rect() const;
	double left() const;
	double right() const;
	double top() const;
	double bottom() const;
	const Point& point() const;
	const Point& direction() const;
	double unit_per_ms() const;
	double x_unit_per_ms() const;
	double y_unit_per_ms() const;
	double have_moved_unit() const;
	void have_moved_unit(double new_value);

	double get_current_x_offset() const;
	double get_current_y_offset() const;
	double get_x_difference_to(const Piece& destination) const;
	double get_y_difference_to(const Piece& destination) const;
	bool does_overlap(const Piece& other) const;
};

#endif
