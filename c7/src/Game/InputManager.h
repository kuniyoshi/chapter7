#ifndef BAKUDAN_GAME_INPUT_MANAGER_H_
#define BAKUDAN_GAME_INPUT_MANAGER_H_

namespace Game { namespace Input { class Parent; } }

namespace Game
{

class InputManager
{
public:
    enum UserId
    {
        UserId1,
        UserId2,
    };

    static bool does_user1_exist();
    static bool does_user2_exist();
    static void create();
    static void destroy();
    static InputManager user1();
    static InputManager user2();

private:
    UserId user_id_;

public:
    InputManager(UserId id);
    ~InputManager();
    
    bool is_left()      const;
    bool is_right()     const;
    bool is_top()       const;
    bool is_bottom()    const;
    bool is_action()    const;
    bool is_option()    const;
    bool is_reset()     const;

    bool is_left_triggered()    const;
    bool is_right_triggered()   const;
    bool is_top_triggered()     const;
    bool is_bottom_triggered()  const;
    bool is_action_triggered()  const;
    bool is_option_triggered()  const;
    bool is_reset_triggered()   const;

    void update();

    bool is_test_input_game_success() const;
    bool is_test_input_game_failure() const;
};

} // namespace Game

#endif
