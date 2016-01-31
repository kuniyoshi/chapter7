#ifndef BAKUDAN_GAME_INPUT_KEYBOARD_
#define BAKUDAN_GAME_INPUT_KEYBOARD_
#include "Game/Input/Parent.h"

namespace Game
{

namespace Input
{

class Keyboard : public Input::Parent
{
private:
    char keys_[CommandSize];

public:
    Keyboard(   const char left_key,
                const char right_key,
                const char top_key,
                const char bottom_key,
                const char action_key,
                const char option_key,
                const char reset_key);
    virtual ~Keyboard();
    virtual void update();
    virtual bool isTriggered(const char key) const;
    virtual bool is_left_triggered() const;
    virtual bool is_right_triggered() const;
    virtual bool is_top_triggered() const;
    virtual bool is_bottom_triggered() const;
    virtual bool is_action_triggered() const;
    virtual bool is_option_triggered() const;
    virtual bool is_reset_triggered() const;
};

} // namespace Input

} // namespace Game

#endif
