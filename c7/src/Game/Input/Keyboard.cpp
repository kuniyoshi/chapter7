#include "Game/Input/Keyboard.h"
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"

namespace Game
{

namespace Input
{

Keyboard::Keyboard( const char left_key,
                    const char right_key,
                    const char top_key,
                    const char bottom_key,
                    const char action_key,
                    const char option_key,
                    const char reset_key)
{
    keys_[CommandLeft]      = left_key;
    keys_[CommandRight]     = right_key;
    keys_[CommandTop]       = top_key;
    keys_[CommandBottom]    = bottom_key;
    keys_[CommandAction]    = action_key;
    keys_[CommandOption]    = option_key;
    keys_[CommandReset]     = reset_key;
}

Keyboard::~Keyboard() {}

void Keyboard::update()
{
    GameLib::Input::Keyboard keyboard = GameLib::Input::Manager::instance().keyboard();

    for (int i = 0; i < CommandSize; ++i)
    {
        if (keyboard.isOn(keys_[i]))
        {
            Parent::set_input(static_cast< Parent::Command >(i));
            return;
        }
    }

    Parent::set_false_all();
}

bool Keyboard::isTriggered(const char key) const
{
    return GameLib::Input::Manager::instance().keyboard().isTriggered(key);
}

bool Keyboard::is_left_triggered() const
{
    return isTriggered(keys_[CommandLeft]);
}

bool Keyboard::is_right_triggered() const
{
    return isTriggered(keys_[CommandRight]);
}

bool Keyboard::is_top_triggered() const
{
    return isTriggered(keys_[CommandTop]);
}

bool Keyboard::is_bottom_triggered() const
{
    return isTriggered(keys_[CommandBottom]);
}

bool Keyboard::is_action_triggered() const
{
    return isTriggered(keys_[CommandAction]);
}

bool Keyboard::is_option_triggered() const
{
    return isTriggered(keys_[CommandOption]);
}

bool Keyboard::is_reset_triggered() const
{
    return isTriggered(keys_[CommandReset]);
}

} // namespace Input

} // namespace Game
