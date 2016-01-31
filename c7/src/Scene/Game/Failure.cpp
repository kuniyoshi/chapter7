#include "Scene/Game/Failure.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Game/InputManager.h"
#include "State.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName Failure::Name_ = Controller::Game::SceneFailure;

Failure::Failure()
: play_mode_(Constants::PlayMode1P)
{}

Failure::Failure(Constants::PlayMode play_mode)
: play_mode_(play_mode)
{}

Failure::~Failure() {}

Controller::Game::SceneName Failure::name() const { return Name_; }

void Failure::update(State* state, Controller::Game::SceneName* next_scene_name)
{
    GameLib::Framework f = GameLib::Framework::instance();

    ::Game::InputManager user_input = ::Game::InputManager::user1();
    user_input.update();

    if (user_input.is_option())
    {
        *next_scene_name = Controller::Game::SceneNoStateGameOver;
    }

    f.drawDebugString(0, 0, "FAILURE!!!", 0xffffffff);
    state->draw();
}

} // namespace Game

} // namespace Scene
