#ifndef BAKUDAN_SCENE_NOSTATE_ENDING_H_
#define BAKUDAN_SCENE_NOSTATE_ENDING_H_

#include "Scene/NoState/Parent.h"
#include "Controller/NoState.h"
#include "Controller/Game.h"
#include "Constants.h"

namespace Scene
{

namespace NoState
{

class Ending : public Scene::NoState::Parent
{
private:
	static const Controller::NoState::SceneName Name_;

public:
	Ending();
	virtual ~Ending();
	virtual Controller::NoState::SceneName name() const;
	virtual void update(	Controller::NoState::SceneName* next_scene_name,
							Constants::PlayMode*);
};

} // namespace NoState

} // namespace Scene

#endif
