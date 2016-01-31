#ifndef BAKUDAN_GAME_INPUT_PARENT_H_
#define BAKUDAN_GAME_INPUT_PARENT_H_

namespace Game
{

namespace Input
{

class Parent
{
public:
    enum Command
    {
        CommandLeft,
        CommandRight,
        CommandTop,
        CommandBottom,
        CommandAction,
        CommandOption,
        CommandReset,

        CommandSize,
    };

private:
    bool inputs_[CommandSize];

public:
    Parent();
    virtual ~Parent();
    virtual bool is_left() const;
    virtual bool is_right() const;
    virtual bool is_top() const;
    virtual bool is_bottom() const;
    virtual bool is_action() const;
    virtual bool is_option() const;
    virtual bool is_reset() const;
    virtual void set_input(Command command);
    virtual void update() = 0;
    virtual void set_false_all();
};

} // namespace Input

} // namespace Game

#endif
