#include "Game/Input/Parent.h"

namespace Game
{

namespace Input
{

Parent::Parent()
{
    for (int i = 0; i < CommandSize; ++i)
    {
        inputs_[i] = false;
    }
}

Parent::~Parent() {}

bool Parent::is_left()      const { return inputs_[CommandLeft]; }
bool Parent::is_right()     const { return inputs_[CommandRight]; }
bool Parent::is_top()       const { return inputs_[CommandTop]; }
bool Parent::is_bottom()    const { return inputs_[CommandBottom]; }
bool Parent::is_action()    const { return inputs_[CommandAction]; }
bool Parent::is_option()    const { return inputs_[CommandOption]; }
bool Parent::is_reset()     const { return inputs_[CommandReset]; }

void Parent::set_input(Command command)
{
    for (int i = 0; i < CommandSize; ++i)
    {
        inputs_[i] = (i == command);
    }
}

void Parent::set_false_all()
{
    for (int i = 0; i < CommandSize; ++i)
    {
        inputs_[i] = false;
    }
}

} // namespace Input

} // namespace Game
