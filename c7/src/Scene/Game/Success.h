#ifndef BAKUDAN_SCENE_GAME_SUCCESS_H_
#define BAKUDAN_SCENE_GAME_SUCCESS_H_

#include "Scene/Game/Parent.h"
#include "Controller/Game.h"
#include "Constants.h"

class State;

namespace Scene
{

namespace Game
{

class Success : public Scene::Game::Parent
{
private:
	static const Controller::Game::SceneName Name_;

private:
	Constants::PlayMode play_mode_;

public:
	Success();
	Success(Constants::PlayMode play_mode);
	virtual ~Success();
	virtual Controller::Game::SceneName name() const;
	virtual void update(State* state, Controller::Game::SceneName* next_scene_name);
};

} // namespace Game

} // namespace Scene

#endif
