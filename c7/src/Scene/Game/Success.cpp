#include "Scene/Game/Success.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Game/InputManager.h"
#include "State.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName Success::Name_ = Controller::Game::SceneSuccess;

Success::Success()
: play_mode_(Constants::PlayMode1P)
{}

Success::Success(Constants::PlayMode play_mode)
: play_mode_(play_mode)
{}

Success::~Success() {}

Controller::Game::SceneName Success::name() const { return Name_; }

void Success::update(State* state, Controller::Game::SceneName* next_scene_name)
{
    GameLib::Framework f = GameLib::Framework::instance();
    ::Game::InputManager user1_input = ::Game::InputManager::user1();

    if (user1_input.is_option())
    {
        *next_scene_name = Controller::Game::SceneNoStateEnding;
    }

    f.drawDebugString(0, 0, "SUCCESS!!!", 0xffffffff);
    state->draw();
}

} // namespace Game

} // namespace Scene
