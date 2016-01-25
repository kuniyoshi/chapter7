#ifndef BAKUDAN_GAME_EVENT_BURN
#define BAKUDAN_GAME_EVENT_BURN
#include "Game/Event/Parent.h"

namespace Game
{

namespace Event
{

class Burn : public Parent
{
private:
    unsigned duration_;
    unsigned ms_to_completion_;
    unsigned ms_to_fade_;

public:
    Burn(unsigned now, unsigned ms_to_completion);
    virtual ~Burn();
    virtual bool did_complete() const;
    virtual double get_alpha() const;
    virtual void tick(unsigned now);
};

} // namespace Event

} // namespace Game

#endif
