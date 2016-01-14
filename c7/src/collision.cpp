#include "collision.h"
#include <cmath>
#include "Piece.h"
#include "Point.h"

namespace collision
{

namespace
{

template< class T >
T mymin(T a, T b) { return b < a ? b : a; }

template< class T >
T mymax(T a, T b) { return b > a ? b : a; }

bool will_not_collision_occur_at_soon(const Piece& a, const Piece& b)
{
	Point diff = b.point() - a.point();
	int length = std::abs(diff.x()) + std::abs(diff.y());
	int pessimistic_length = length - 2;
	return pessimistic_length - 2 > 0;
}

template< class T >
bool is_sign_differ(T a, T b)
{
	if (a == 0 || b == 0)
	{
		return false;
	}

	bool is_a_positive = a > -a;
	bool is_b_positive = b > -b;

	return is_a_positive != is_b_positive;
}

template< class T >
bool is_sign_same(T a, T b)
{
	if (a == 0 && a == b)
	{
		return true;
	}

	if (a == 0 || b == 0)
	{
		return false;
	}

	bool is_a_positive = a > -a;
	bool is_b_positive = b > -b;

	return is_a_positive == is_b_positive;
}

bool set_same_axis_collision_ms(const Piece& a, const Piece& b, unsigned* ms)
{
	Point point_diff = b.point() - a.point();
	bool is_x_same(point_diff.x() == 0);
	bool is_y_same(point_diff.y() == 0);

	if (!is_x_same && !is_y_same)
	{
		return false;
	}

	if (a.does_overlap(b))
	{
		*ms = 0;
		return true;
	}

	unsigned ms_candidate(0);

	if (is_y_same)
	{
		double denominator(a.x_unit_per_ms() - b.x_unit_per_ms());

		if (denominator == 0.0)
		{
			return false;
		}

		double numerator(a.get_x_difference_to(b));

		if (is_sign_differ(denominator, numerator))
		{
			return false;
		}

		ms_candidate = static_cast< unsigned >(numerator / denominator);

		if (a.direction().y() == 0 && b.direction().y() == 0)
		{
			*ms = ms_candidate;
			return true;
		}

		Piece new_a(a);
		new_a.have_moved_unit(	new_a.have_moved_unit()
								+ new_a.unit_per_ms() * ms_candidate);
		Piece new_b(b);
		new_b.have_moved_unit(	new_b.have_moved_unit()
								+ new_b.unit_per_ms() * ms_candidate);

		if (a.does_overlap(b))
		{
			*ms = ms_candidate;
			return true;
		}

		return false;
	}
	else if (is_x_same)
	{
		double denominator(a.y_unit_per_ms() - b.y_unit_per_ms());

		if (denominator == 0.0)
		{
			return false;
		}

		double numerator(a.get_y_difference_to(b));

		if (is_sign_differ(denominator, numerator))
		{
			return false;
		}

		ms_candidate = static_cast< unsigned >(numerator / denominator);

		if (a.direction().x() == 0 && b.direction().x() == 0)
		{
			*ms = ms_candidate;
			return true;
		}

		Piece new_a(a);
		new_a.have_moved_unit(	new_a.have_moved_unit()
								+ new_a.unit_per_ms() * ms_candidate);
		Piece new_b(b);
		new_b.have_moved_unit(	new_b.have_moved_unit()
								+ new_b.unit_per_ms() * ms_candidate);

		if (a.does_overlap(b))
		{
			*ms = ms_candidate;
			return true;
		}

		return false;
	}

	return false;
}

bool is_going_to(const Piece& piece, const Point& point)
{
	Point diff_point = point - piece.point();
	return is_sign_same(piece.direction().x(), diff_point.x())
		&& is_sign_same(piece.direction().y(), diff_point.y());
}

bool set_cross_axis_collision_ms(const Piece& a, const Piece& b, unsigned* ms)
{
	Point point_diff = b.point() - a.point();
	bool is_x_same(point_diff.x() == 0);
	bool is_y_same(point_diff.y() == 0);

	if (is_x_same || is_y_same)
	{
		return false;
	}

	Point min_point(	mymin(a.point().x(), b.point().x()),
						mymin(a.point().y(), b.point().y()));
	Point max_point(	mymax(a.point().x(), b.point().x()),
						mymax(a.point().y(), b.point().y()));

	bool are_both_going_to_min(is_going_to(a, min_point) && is_going_to(b, min_point));
	bool are_both_going_to_max(is_going_to(a, max_point) && is_going_to(b, max_point));

	if (!are_both_going_to_min && !are_both_going_to_max)
	{
		return false;
	}

	Piece new_a(a);
	Piece new_b(b);

	if (are_both_going_to_min)
	{
		const Piece* left_point = 0;
		const Piece* right_point = 0;

		if (a.point().x() > min_point.x())
		{
			right_point = &a;
			left_point = &b;
		}
		else
		{
			left_point = &a;
			right_point = &b;
		}

		double length_x_to_min(	(	right_point->point().x()
									+ right_point->get_current_x_offset()
									+ right_point->left())
								- (min_point.x() + left_point->right()));

		if (length_x_to_min < 0)
		{
			*ms = 0;
			return true;
		}

		unsigned ms_x_goes_to_min(0);

		if (right_point->unit_per_ms() != 0.0)
		{
			ms_x_goes_to_min = static_cast< unsigned >(	length_x_to_min
														/ right_point->unit_per_ms());
		}

		double length_y_to_min(	(	left_point->point().y()
									+ left_point->get_current_y_offset()
									+ left_point->top())
								- (min_point.y() + right_point->bottom()));
		unsigned ms_y_goes_to_min(0);

		if (length_y_to_min < 0)
		{
			*ms = 0;
			return true;
		}

		if (left_point->unit_per_ms() != 0.0)
		{
			ms_y_goes_to_min = static_cast< unsigned >(	length_y_to_min
														/ left_point->unit_per_ms());
		}

		unsigned max_ms(mymax(ms_x_goes_to_min, ms_y_goes_to_min));
		new_a.have_moved_unit(	new_a.have_moved_unit()
								+ new_a.unit_per_ms() * max_ms);
		new_b.have_moved_unit(	new_b.have_moved_unit()
								+ new_b.unit_per_ms() * max_ms);

		if (a.does_overlap(b))
		{
			*ms = max_ms;
			return true;
		}

		return false;
	}
	else if (are_both_going_to_max)
	{
		const Piece* left_point = 0;
		const Piece* right_point = 0;

		if (a.point().y() > max_point.y())
		{
			right_point = &a;
			left_point = &b;
		}
		else
		{
			right_point = &a;
			left_point = &b;
		}

		double length_y_to_max(	max_point.y() + left_point->top()
								- (	right_point->point().y()
									+ right_point->get_current_y_offset()
									+ right_point->bottom()));
		unsigned ms_y_goes_to_max(0);

		if (length_y_to_max < 0)
		{
			*ms = 0;
			return true;
		}

		if (right_point->unit_per_ms() != 0.0)
		{
			ms_y_goes_to_max = static_cast< unsigned >(	length_y_to_max
														/ right_point->unit_per_ms());
		}

		double length_x_to_max(	max_point.x() + right_point->left()
								- (	left_point->point().x()
									+ left_point->get_current_x_offset()
									+ left_point->right()));
		unsigned ms_x_goes_to_max(0);

		if (length_x_to_max < 0)
		{
			*ms = 0;
			return true;
		}

		if (left_point->unit_per_ms() != 0.0)
		{
			ms_x_goes_to_max = static_cast< unsigned >(	length_x_to_max
														/ left_point->unit_per_ms());
		}

		unsigned max_ms(mymax(ms_y_goes_to_max, ms_x_goes_to_max));
		new_a.have_moved_unit(	new_a.have_moved_unit()
								+ new_a.unit_per_ms() * max_ms);
		new_b.have_moved_unit(	new_b.have_moved_unit()
								+ new_b.unit_per_ms() * max_ms);

		if (a.does_overlap(b))
		{
			*ms = max_ms;
			return true;
		}

		return false;
	}

	return false;
}

} // namespace -

bool set_ms_at_collision_occur(const Piece& a, const Piece& b, unsigned* ms)
{
	bool did_collision(false);
	bool is_a_moving(a.direction().scalar() != 0);
	bool is_b_moving(b.direction().scalar() != 0);

	// stopping makes no collision
	if (!is_a_moving && !is_b_moving)
	{
		return false;
	}

	if (will_not_collision_occur_at_soon(a, b))
	{
		return false;
	}

	Point diff = b.point() - a.point();
	bool is_x_same(diff.x() == 0);
	bool is_y_same(diff.y() == 0);

	if (is_x_same || is_y_same)
	{
		did_collision = set_same_axis_collision_ms(a, b, ms);
		return did_collision;
	}
	else
	{
		did_collision = set_cross_axis_collision_ms(a, b, ms);
		return did_collision;
	}
}

} // namespace collision
