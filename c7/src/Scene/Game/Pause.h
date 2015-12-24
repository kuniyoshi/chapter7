#ifndef BAKUDAN_SCENE_GAME_PAUSE_H_
#define BAKUDAN_SCENE_GAME_PAUSE_H_

#include "Scene/Game/Parent.h"
#include "Controller/Game.h"
#include "Constants.h"
#include "Iterator/Loop.h"

class State;

namespace Scene
{

namespace Game
{

class Pause : public Scene::Game::Parent
{
private:
	static const Controller::Game::SceneName Name_;

private:
	Constants::PlayMode play_mode_;
	Iterator::Loop looped_index_;

public:
	Pause();
	Pause(Constants::PlayMode play_mode);
	virtual ~Pause();
	virtual Controller::Game::SceneName name() const;
	virtual void update(State* state, Controller::Game::SceneName* next_scene_name);
};

} // namespace Game

} // namespace Scene

#endif
