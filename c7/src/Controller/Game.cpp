#include "Controller/Game.h"
#include "GameLib/GameLib.h"
#include "App.h"
#include "Controller/NoState.h"
#include "State.h"
#include "Constants.h"
#include "Scene/Game/Failure.h"
#include "Scene/Game/Load.h"
#include "Scene/Game/Pause.h"
#include "Scene/Game/Play.h"
#include "Scene/Game/Success.h"
#include "Scene/Game/WinLose.h"

namespace Controller
{

const App::ControllerType Game::Type_ = App::ControllerGame;

Game::Game()
: play_mode_(Constants::PlayMode1P), state_(0), scene_(0)
{
	set_scene(new Scene::Game::Load(play_mode_));
}

Game::Game(Constants::PlayMode play_mode)
: play_mode_(play_mode), state_(0), scene_(0)
{
	set_scene(new Scene::Game::Load(play_mode_));
}

Game::~Game()
{
	SAFE_DELETE(state_);
	delete_scene();
}

App::ControllerType Game::type() const { return Type_; }

void Game::update(	App::ControllerType* next_controller_type,
					Controller::NoState::SceneName* next_no_state_scene_name)
{
	Game::SceneName next_scene_name = scene_->name();

	scene_->update(state_, &next_scene_name);

	if (next_scene_name == scene_->name())
	{
		return;
	}

	if (next_scene_name == SceneLoad)
	{
		delete_scene();
		set_scene(new Scene::Game::Load(play_mode_));
	}
	else if (next_scene_name == ScenePlay)
	{
		delete_scene();
		set_scene(new Scene::Game::Play(play_mode_));
	}
	else if (next_scene_name == ScenePause)
	{
		delete_scene();
		set_scene(new Scene::Game::Pause(play_mode_));
	}
	else if (next_scene_name == SceneSuccess)
	{
		delete_scene();
		set_scene(new Scene::Game::Success(play_mode_));
	}
	else if (next_scene_name == SceneWinLose)
	{
		delete_scene();
		set_scene(new Scene::Game::WinLose(play_mode_));
	}
	else if (next_scene_name == SceneFailure)
	{
		delete_scene();
		set_scene(new Scene::Game::Failure(play_mode_));
	}
	else if (next_scene_name == SceneNoStateTitle)
	{
		delete_scene();
		*next_controller_type = App::ControllerNoState;
		*next_no_state_scene_name = Controller::NoState::SceneTitle;
	}
	else if (next_scene_name == SceneNoStateEnding)
	{
		delete_scene();
		*next_controller_type = App::ControllerNoState;
		*next_no_state_scene_name = Controller::NoState::SceneEnding;
	}
	else if (next_scene_name == SceneNoStateGameOver)
	{
		delete_scene();
		*next_controller_type = App::ControllerNoState;
		*next_no_state_scene_name = Controller::NoState::SceneGameOver;
	}
	else
	{
		HALT("Invalid Scene!!");
	}
}

void Game::delete_scene() { SAFE_DELETE(scene_); }

void Game::set_scene(Scene::Game::Parent* new_scene)
{
	if (new_scene == scene_)
	{
		return;
	}

	delete_scene();
	scene_ = new_scene;
}

} // namespace Controller
