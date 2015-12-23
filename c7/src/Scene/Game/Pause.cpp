#include "Scene/Game/Pause.h"
#include "GameLib/Framework.h"
#include "Controller/Game.h"
#include "State.h"
#include "Constants.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName Pause::Name_ = Controller::Game::ScenePause;

Pause::Pause()
: play_mode_(Constants::PlayMode1P)
{}

Pause::Pause(Constants::PlayMode play_mode)
: play_mode_(play_mode)
{}

Pause::~Pause() {}

Controller::Game::SceneName Pause::name() const { return Name_; }

void Pause::update(State* state, Controller::Game::SceneName* next_scene_name)
{
	GameLib::Framework f = GameLib::Framework::instance();
	f.drawDebugString(0, 0, "Pausing...", 0xffffffff);
	state->draw();
}

} // namespace Game

} // namespace Scene
