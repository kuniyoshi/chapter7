#include "App.h"
#include "GameLib/GameLib.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Controller/NoState.h"
#include "Game/InputManager.h"

App::App()
: game_controller_(0), no_state_controller_(0)
{
    no_state_controller_ = new Controller::NoState();
    Game::InputManager::create();
}

App::~App()
{
    SAFE_DELETE(game_controller_);
    SAFE_DELETE(no_state_controller_);
    Game::InputManager::destroy();
}

void App::update()
{
    ControllerType current_controller_type = game_controller_ ? ControllerGame : ControllerNoState;
    ControllerType next_controller_type = current_controller_type;
    Constants::PlayMode play_mode;
    Controller::NoState::SceneName scene_name;

    if (current_controller_type == ControllerGame)
    {
        game_controller_->update(&next_controller_type, &scene_name);
    }
    else if (current_controller_type == ControllerNoState)
    {
        no_state_controller_->update(&next_controller_type, &play_mode);
    }
    else
    {
        HALT("Invalid next_controller_type");
    }

    if (next_controller_type == current_controller_type)
    {
        return;
    }

    if (next_controller_type == ControllerGame)
    {
        SAFE_DELETE(no_state_controller_);
        game_controller_ = new Controller::Game(play_mode);
    }
    else if (next_controller_type == ControllerNoState)
    {
        SAFE_DELETE(game_controller_);
        no_state_controller_ = new Controller::NoState(scene_name);
    }
    else
    {
        HALT("Invalid controller found!");
    }
}

bool App::was_terminate_requested() const
{
    if (Game::InputManager::does_user1_exist() && Game::InputManager::user1().is_reset())
    {
        return true;
    }
    if (Game::InputManager::does_user2_exist() && Game::InputManager::user2().is_reset())
    {
        return true;
    }
    return false;
}
