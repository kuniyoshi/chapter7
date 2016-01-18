#include "Game/Event/Eat.h"

namespace Game
{

namespace Event
{

Eat::Eat(unsigned now, unsigned ms_to_completion)
:	Parent(now),
	duration_(0), ms_to_completion_(ms_to_completion)
{}

bool Eat::did_complete() const { return duration_ > ms_to_completion_; }

void Eat::tick(unsigned now)
{
	if (Parent::is_pausing())
	{
		return;
	}

	unsigned diff = now - Parent::last_stamp();
	Parent::last_stamp(now);
	duration_ = duration_ + diff;
}

} // namespace Event

} // namespace Game
