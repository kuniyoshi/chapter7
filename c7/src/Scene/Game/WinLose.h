#ifndef BAKUDAN_SCENE_GAME_WINLOSE_H_
#define BAKUDAN_SCENE_GAME_WINLOSE_H_

#include "Scene/Game/Parent.h"
#include "Controller/Game.h"
#include "Constants.h"

class State;

namespace Scene
{

namespace Game
{

class WinLose : public Scene::Game::Parent
{
private:
	static const Controller::Game::SceneName Name_;

private:
	Constants::PlayMode play_mode_;

public:
	WinLose();
	WinLose(Constants::PlayMode play_mode);
	virtual ~WinLose();
	virtual Controller::Game::SceneName name() const;
	virtual void update(State* state, Controller::Game::SceneName* next_scene_name);
};

} // namespace Game

} // namespace Scene

#endif
