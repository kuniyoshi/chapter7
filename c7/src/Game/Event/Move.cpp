#include "Game/Event/Move.h"
#include "Point.h"

namespace Game
{

namespace Event
{

Move::Move(unsigned now, const Point& from, const Point& direction)
:	Parent(now),
	point_(from), direction_(direction),
	ms_per_units_(2000), duration_(0), did_complete_(false)
{}
Move::~Move() {}

const Point& Move::point() const { return point_; }

bool Move::did_complete() const { return did_complete_; }

void Move::tick(unsigned now)
{
	if (Parent::is_pausing())
	{
		return;
	}

	if (did_complete_)
	{
		return;
	}

	unsigned diff = now - Parent::last_stamp();
	Parent::last_stamp(now);

	duration_ = duration_ + diff;

	did_complete_ = duration_ > ms_per_units_;
}

double Move::completion_rate() const
{
	if (duration_ >= ms_per_units_)
	{
		return 1.0;
	}
	return static_cast< double >(duration_) / static_cast< double >(ms_per_units_);
}

int Move::dx() const { return direction_.x(); }
int Move::dy() const { return direction_.y(); }

bool Move::can_reverse_by(const Point& new_direction) const
{
	if (did_complete_)
	{
		return false;
	}
	Point diff = direction_ + new_direction;
	return diff.scalar() == 0;
}

void Move::reverse()
{
	duration_ = ms_per_units_ - duration_;
	point_ = point_ + direction_;
	direction_ = Point(0, 0) - direction_;
}

} // namespace Event

} // namespace Game
