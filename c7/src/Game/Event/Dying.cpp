#include "Game/Event/Dying.h"

namespace Game
{

namespace Event
{

Dying::Dying(unsigned now, unsigned ms_to_completion)
:	Parent(now),
	duration_(0), ms_to_completion_(ms_to_completion)
{}

bool Dying::did_complete() const { return duration_ > ms_to_completion_; }

double Dying::completion_rate() const
{
	if (did_complete())
	{
		return 1.0;
	}

	return static_cast< double >(duration_) / ms_to_completion_;
}

void Dying::tick(unsigned now)
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
