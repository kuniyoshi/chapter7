#ifndef BAKUDAN_CONTROLLER_GAME_H_
#define BAKUDAN_CONTROLLER_GAME_H_

#include "App.h"
#include "Controller/Parent.h"
#include "Controller/NoState.h"
#include "Constants.h"

class State;

namespace Scene
{

namespace Game
{

class Parent;

} // namespace Game

} // namespace Scene


namespace Controller
{

class Game : public Parent
{
public:
	enum SceneName
	{
		SceneLoad,
		ScenePlay,
		ScenePause,
		SceneSuccess,
		SceneFailure,
		SceneWinLose,

		SceneNoStateGameOver,
		SceneNoStateEnding,
		SceneNoStateTitle,
	};

private:
	static const App::ControllerType Type_;

private:
	Constants::PlayMode play_mode_;
	State* state_;
	Scene::Game::Parent* scene_;

public:
	Game();
	Game(Constants::PlayMode play_mode);
	virtual ~Game();
	virtual App::ControllerType type() const;
	virtual void update(	App::ControllerType* next_controller_type,
							Controller::NoState::SceneName* scene_name);
	void delete_scene();
	void set_scene(Scene::Game::Parent* new_scene);
};

} // namespace Controller

#endif
