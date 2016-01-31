#include "Game/InputManager.h"
#include "GameLib/GameLib.h"
#include "Game/Input/Parent.h"
#include "Game/Input/Keyboard.h"

namespace Game
{

namespace
{

Input::Keyboard* g_user1 = 0;
Input::Keyboard* g_user2 = 0;

} // namespace -

bool InputManager::does_user1_exist() { return !!g_user1; }
bool InputManager::does_user2_exist() { return !!g_user2; }

void InputManager::create()
{
    g_user1 = new Input::Keyboard('A', 'S', 'W', 'Z', 'F', ' ', 'T');
    g_user2 = new Input::Keyboard('H', 'L', 'K', 'J', 'O', ' ', 'Y');
}

void InputManager::destroy()
{
    SAFE_DELETE(g_user1);
    SAFE_DELETE(g_user2);
}

InputManager InputManager::user1()
{
    ASSERT(g_user1);
    g_user1->update();
    return InputManager(UserId1);
}

InputManager InputManager::user2()
{
    ASSERT(g_user2);
    g_user2->update();
    return InputManager(UserId2);
}

InputManager::InputManager(UserId user_id)
: user_id_(user_id)
{
    ASSERT(g_user1);
    ASSERT(g_user2);
}

InputManager::~InputManager() {}

namespace
{

Input::Keyboard* get_g_user(InputManager::UserId user_id)
{
    if (user_id == InputManager::UserId1)
    {
        return g_user1;
    }
    else
    {
        return g_user2;
    }
}

} // namespace -

bool InputManager::is_left() const { return get_g_user(user_id_)->is_left(); }
bool InputManager::is_right() const { return get_g_user(user_id_)->is_right(); }
bool InputManager::is_top() const { return get_g_user(user_id_)->is_top(); }
bool InputManager::is_bottom() const { return get_g_user(user_id_)->is_bottom(); }
bool InputManager::is_action() const { return get_g_user(user_id_)->is_action(); }
bool InputManager::is_option() const { return get_g_user(user_id_)->is_option(); }
bool InputManager::is_reset() const { return get_g_user(user_id_)->is_reset(); }

bool InputManager::is_left_triggered() const
{
    return get_g_user(user_id_)->is_left_triggered();
}
bool InputManager::is_right_triggered() const
{
    return get_g_user(user_id_)->is_right_triggered();
}
bool InputManager::is_top_triggered() const
{
    return get_g_user(user_id_)->is_top_triggered();
}
bool InputManager::is_bottom_triggered() const
{
    return get_g_user(user_id_)->is_bottom_triggered();
}
bool InputManager::is_action_triggered() const
{
    return get_g_user(user_id_)->is_action_triggered();
}
bool InputManager::is_option_triggered() const
{
    return get_g_user(user_id_)->is_option_triggered();
}
bool InputManager::is_reset_triggered() const
{
    return get_g_user(user_id_)->is_reset_triggered();
}

void InputManager::update() { get_g_user(user_id_)->update(); }

bool InputManager::is_test_input_game_success() const
{
#ifndef NDEBUG
    return g_user1->isTriggered('G');
#endif
 return false;
}

bool InputManager::is_test_input_game_failure() const
{
#ifndef NDEBUG
    return g_user1->isTriggered('B');
#endif
 return false;
}

} // namespace Game
