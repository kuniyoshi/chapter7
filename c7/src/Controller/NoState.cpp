#include "Controller/NoState.h"
#include "GameLib/GameLib.h"
#include "App.h"
#include "Controller/Game.h"
#include "Scene/NoState/Parent.h"
#include "Scene/NoState/Ending.h"
#include "Scene/NoState/GameOver.h"
#include "Scene/NoState/Title.h"
#include "Constants.h"

namespace Controller
{

const App::ControllerType NoState::Type_ = App::ControllerNoState;

NoState::NoState()
: scene_(0)
{
	set_scene(new Scene::NoState::Title());
}

NoState::NoState(SceneName scene_name)
: scene_(0)
{
	if (scene_name == SceneTitle)
	{
		set_scene(new Scene::NoState::Title());
	}
	else if (scene_name == SceneEnding)
	{
		set_scene(new Scene::NoState::Ending());
	}
	else if (scene_name == SceneGameOver)
	{
		set_scene(new Scene::NoState::GameOver());
	}
	else
	{
		HALT("Invalid scene_name");
	}
}

NoState::~NoState()
{
	delete_scene();
}

App::ControllerType NoState::type() const { return NoState::Type_; }

void NoState::update(	App::ControllerType* controller_type,
						Constants::PlayMode* play_mode)
{
	NoState::SceneName next_scene_name = scene_->name();

	scene_->update(&next_scene_name, play_mode);

	if (next_scene_name == scene_->name())
	{
		return;
	}

	if (next_scene_name == SceneTitle)
	{
		delete_scene();
		set_scene(new Scene::NoState::Title());
	}
	else if (next_scene_name == SceneEnding)
	{
		delete_scene();
		set_scene(new Scene::NoState::Ending());
	}
	else if (next_scene_name == SceneGameOver)
	{
		delete_scene();
		set_scene(new Scene::NoState::GameOver());
	}
	else if (next_scene_name == SceneGame)
	{
		delete_scene();
		*controller_type = App::ControllerGame;
	}
	else {
		HALT("Invalid scene!!!");
	}
}

void NoState::delete_scene() { SAFE_DELETE(scene_); }

void NoState::set_scene(Scene::NoState::Parent* new_scene)
{
	if (new_scene == scene_)
	{
		return;
	}

	delete_scene();
	scene_ = new_scene;
}

} // namespace Controller
