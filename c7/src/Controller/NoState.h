#ifndef BAKUDAN_CONTROLLER_NOSTATE_H_
#define BAKUDAN_CONTROLLER_NOSTATE_H_

#include "App.h"
#include "Controller/Parent.h"
#include "Constants.h"

namespace Scene
{

namespace NoState
{

class Parent;

} // namespace NoState

} // namespace Scene

namespace Controller
{

class NoState : public Parent
{
public:
	enum SceneName
	{
		SceneTitle,
		SceneEnding,
		SceneGameOver,
		SceneGame,
	};

private:
	static const App::ControllerType Type_;

private:
	Scene::NoState::Parent* scene_;

public:
	NoState();
	NoState(SceneName scene_name);
	virtual ~NoState();
	virtual App::ControllerType type() const;
	virtual void update(	App::ControllerType* controller_type,
							Constants::PlayMode* play_mode);
	void delete_scene();
	void set_scene(Scene::NoState::Parent* new_scene);
};

} // namespace Controller

#endif
