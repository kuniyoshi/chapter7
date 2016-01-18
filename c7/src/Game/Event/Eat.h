#ifndef BAKUDAN_GAME_EVENT_EAT
#define BAKUDAN_GAME_EVENT_EAT
#include "Game/Event/Parent.h"

namespace Game
{

namespace Event
{

class Eat : public Parent
{
private:
	unsigned duration_;
	unsigned ms_to_completion_;

public:
	Eat(unsigned now, unsigned ms_to_completion);
	bool did_complete() const;
	double completion_rate() const;
	int completion_rate(int max) const;
	void tick(unsigned now);
};

} // namespace Event

} // namespace Game

#endif
