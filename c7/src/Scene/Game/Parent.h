#ifndef BAKUDAN_SCENE_GAME_PARENT_H_
#define BAKUDAN_SCENE_GAME_PARENT_H_

#include "Scene/Parent.h"
#include "Controller/Game.h"

class State;

namespace Scene
{

namespace Game
{

class Parent : public Scene::Parent
{
public:
	Parent();
	virtual ~Parent();

	virtual Controller::Game::SceneName name() const = 0;
	virtual void update(State* state, Controller::Game::SceneName* next_scene_name) = 0;
};

} // namespace Game

} // namespace Scene

#endif
