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
	unsigned ms_per_units_;
	unsigned duration_;
	bool did_complete_;

public:
	Move(unsigned now, const Point& from, const Point& direction);
	virtual ~Move();
	const Point& point() const;
	bool did_complete() const;
	virtual void tick(unsigned now);
	double completion_rate() const;
	int dx() const;
	int dy() const;
	bool can_reverse_by(const Point& new_direction) const;
	void reverse();
};

} // namespace Event

} // namespace Game

#endif
