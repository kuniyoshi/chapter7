#include "Scene/Game/Success.h"
#include "GameLib/Framework.h"
#include "Controller/Game.h"
#include "State.h"
#include "Constants.h"

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

	if (f.isKeyTriggered(' '))
	{
		*next_scene_name = Controller::Game::SceneNoStateEnding;
	}

	f.drawDebugString(0, 0, "SUCCESS!!!", 0xffffffff);
	state->draw();
}

} // namespace Game

} // namespace Scene
