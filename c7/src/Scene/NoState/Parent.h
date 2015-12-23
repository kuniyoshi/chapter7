#ifndef BAKUDAN_SCENE_NOSTATE_PARENT_H_
#define BAKUDAN_SCENE_NOSTATE_PARENT_H_

#include "Scene/Parent.h"
#include "Controller/NoState.h"
#include "Constants.h"

namespace Scene
{

namespace NoState
{

class Parent : public Scene::Parent
{
public:
	Parent();
	virtual ~Parent();

	virtual Controller::NoState::SceneName name() const = 0;
	virtual void update(	Controller::NoState::SceneName* next_scene_name,
							Constants::PlayMode* play_mode) = 0;
};

} // namespace NoState

} // namespace Scene

#endif
