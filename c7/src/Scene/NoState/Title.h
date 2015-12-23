#ifndef BAKUDAN_SCENE_NOSTATE_TITLE_H_
#define BAKUDAN_SCENE_NOSTATE_TITLE_H_

#include "Scene/NoState/Parent.h"
#include "Iterator/Loop.h"
#include "Controller/NoState.h"
#include "Controller/Game.h"
#include "Constants.h"

namespace Scene
{

namespace NoState
{

class Title : public Scene::NoState::Parent
{
private:
	static const Controller::NoState::SceneName Name_;

private:
	Iterator::Loop looped_index_;

public:
	Title();
	virtual ~Title();
	virtual Controller::NoState::SceneName name() const;
	virtual void update(	Controller::NoState::SceneName* next_scene_name,
							Constants::PlayMode* play_mode);
};

} // namespace NoState

} // namespace Scene

#endif
