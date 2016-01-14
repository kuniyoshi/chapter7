#ifndef BAKUDAN_GAME_EVENT_MOVE_H_
#define BAKUDAN_GAME_EVENT_MOVE_H_
#include "Game/Event/Parent.h"
#include "Point.h"

namespace Game
{

namespace Event
{

class Move : public Parent
{
private:
	Point point_;
	Point direction_;
	unsigned ms_per_unit_;
	unsigned duration_;
	bool did_complete_;

public:
	Move(unsigned now, const Point& from, const Point& direction);
	virtual ~Move();
	const Point& point() const;
	const Point& direction() const;
	unsigned ms_per_unit() const;
	bool did_complete() const;
	virtual void tick(unsigned now);
	void tick_with_no_duration(unsigned now);
	void tick_until(unsigned now, unsigned ms_max, bool* did_consume_all);
	double completion_rate() const;
	int dx() const;
	int dy() const;
	bool can_reverse_by(const Point& new_direction) const;
	void reverse();
};

} // namespace Event

} // namespace Game

#endif
