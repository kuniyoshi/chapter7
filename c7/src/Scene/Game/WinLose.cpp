#include "Scene/Game/WinLose.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Game/InputManager.h"
#include "State.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName WinLose::Name_ = Controller::Game::SceneWinLose;

WinLose::WinLose()
: play_mode_(Constants::PlayMode1P)
{}

WinLose::WinLose(Constants::PlayMode play_mode)
: play_mode_(play_mode)
{}

WinLose::~WinLose() {}

Controller::Game::SceneName WinLose::name() const { return Name_; }

void WinLose::update(State* state, Controller::Game::SceneName* next_scene_name)
{
    GameLib::Framework f = GameLib::Framework::instance();
    ::Game::InputManager user1_input = ::Game::InputManager::user1();

    if (user1_input.is_option())
    {
        *next_scene_name = Controller::Game::SceneNoStateTitle;
    }

    f.drawDebugString(0, 0, "win lose", 0xffffffff);
    
    state->draw();
}

} // namespace Game

} // namespace Scene
