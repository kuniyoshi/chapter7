#include "Scene/Game/Play.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Game/InputManager.h"
#include "State.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName Play::Name_ = Controller::Game::ScenePlay;

Play::Play()
: play_mode_(Constants::PlayMode1P)
{}

Play::Play(Constants::PlayMode play_mode)
: play_mode_(play_mode)
{}

Play::~Play() {}

Controller::Game::SceneName Play::name() const { return Name_; }

void Play::update(State* state, Controller::Game::SceneName* next_scene_name)
{
    GameLib::Framework f = GameLib::Framework::instance();
    f.drawDebugString(0, 1, "NOW YOU ARE PLAYING...");

    ::Game::InputManager user_input = ::Game::InputManager::user2();

    if (user_input.is_option_triggered())
    {
        *next_scene_name = Controller::Game::ScenePause;
        state->pause();
    }
    else if (user_input.is_test_input_game_success())
    {
        *next_scene_name = play_mode_ == Constants::PlayMode1P
            ? Controller::Game::SceneSuccess
            : Controller::Game::SceneWinLose;
    }
    else if (play_mode_ == Constants::PlayMode1P && user_input.is_test_input_game_failure())
    {
        *next_scene_name = Controller::Game::SceneFailure;
    }

    state->update();

    if (state->does_game_over())
    {
        *next_scene_name = play_mode_ == Constants::PlayMode1P
            ? Controller::Game::SceneSuccess
            : Controller::Game::SceneWinLose;
    }
    else if (state->does_game_failure())
    {
        *next_scene_name = Controller::Game::SceneFailure;
    }

    state->draw();
}

} // namespace Game

} // namespace Scene
