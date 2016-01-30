#include "Scene/Game/Failure.h"
#include "GameLib/Framework.h"
#include "Controller/Game.h"
#include "State.h"
#include "Constants.h"

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

    if (f.isKeyTriggered(' '))
    {
        *next_scene_name = Controller::Game::SceneNoStateGameOver;
    }

    f.drawDebugString(0, 0, "FAILURE!!!", 0xffffffff);
    state->draw();
}

} // namespace Game

} // namespace Scene
