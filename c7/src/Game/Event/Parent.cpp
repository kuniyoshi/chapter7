#include "Game/Event/Parent.h"

namespace Game
{

namespace Event
{

Parent::Parent()
: last_stamp_(0), is_pausing_(false) {}
Parent::Parent(unsigned now)
: last_stamp_(now), is_pausing_(false) {}
Parent::~Parent() {}

unsigned Parent::last_stamp() const { return last_stamp_; }
void Parent::last_stamp(unsigned now) { last_stamp_ = now; }

bool Parent::is_pausing() const { return is_pausing_; }
void Parent::pause(unsigned now)
{
	last_stamp_ = now;
	is_pausing_ = true;
}
void Parent::resume(unsigned now)
{
	last_stamp_ = now;
	is_pausing_ = false;
}

} // namespace Event

} // namespace Game
