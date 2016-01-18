#ifndef BAKUDAN_GAME_EVENT_DYING_H
#define BAKUDAN_GAME_EVENT_DYING_H
#include "Game/Event/Parent.h"

namespace Game
{

namespace Event
{

class Dying : public Parent
{
private:
	unsigned duration_;
	unsigned ms_to_completion_;

public:
	Dying(unsigned now, unsigned ms_to_completion);
	bool did_complete() const;
	double completion_rate() const;
	void tick(unsigned now);
};

} // namespace Event

} // namespace Game

#endif
