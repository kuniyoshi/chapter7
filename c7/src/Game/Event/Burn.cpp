#include "Game/Event/Burn.h"

namespace Game
{

namespace Event
{

namespace
{

const double BlinkingRate   = 0.8;
const double FedingRate     = 0.2;
const unsigned MsToGroup    = 200;

} // namespace -


Burn::Burn(unsigned now, unsigned ms_to_completion)
:   Parent(now),
    duration_(0), ms_to_completion_(ms_to_completion), ms_to_fade_(0)
{
    ms_to_fade_ = ms_to_completion_ - FedingRate * ms_to_completion_;
}

Burn::~Burn() {}

bool Burn::did_complete() const { return duration_ >= ms_to_completion_; }

double Burn::get_alpha() const
{
    if (did_complete())
    {
        return 0.0;
    }

    if (duration_ > ms_to_fade_)
    {
        unsigned feding_ms = ms_to_completion_ - ms_to_fade_;
        unsigned spent_ms = duration_ - ms_to_fade_;
        return static_cast< double >(spent_ms) / feding_ms;
    }

    int blink_group = duration_ / MsToGroup;
    return blink_group % 2 == 0 ? 1.0 : 0.8;
}

void Burn::tick(unsigned now)
{
    unsigned diff = now - Parent::last_stamp();
    Parent::last_stamp(now);

    duration_ = duration_ + diff;
}

} // namespace Event

} // namespace Game
