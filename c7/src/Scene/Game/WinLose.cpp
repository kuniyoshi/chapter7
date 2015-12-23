#include "Scene/Game/WinLose.h"
#include "GameLib/Framework.h"
#include "Controller/Game.h"
#include "State.h"
#include "Constants.h"

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

	if (f.isKeyTriggered(' '))
	{
		*next_scene_name = Controller::Game::SceneNoStateTitle;
	}

	f.drawDebugString(0, 0, "win lose", 0xffffffff);
	
	state->draw();
}

} // namespace Game

} // namespace Scene
