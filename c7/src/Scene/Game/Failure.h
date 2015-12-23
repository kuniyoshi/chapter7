#ifndef BAKUDAN_SCENE_GAME_FAILURE_H_
#define BAKUDAN_SCENE_GAME_FAILURE_H_

#include "Scene/Game/Parent.h"
#include "Controller/Game.h"
#include "Constants.h"

class State;

namespace Scene
{

namespace Game
{

class Failure : public Scene::Game::Parent
{
private:
	static const Controller::Game::SceneName Name_;

private:
	Constants::PlayMode play_mode_;

public:
	Failure();
	Failure(Constants::PlayMode play_mode);
	virtual ~Failure();
	virtual Controller::Game::SceneName name() const;
	virtual void update(State* state, Controller::Game::SceneName* next_scene_name);
};

} // namespace Game

} // namespace Scene

#endif
