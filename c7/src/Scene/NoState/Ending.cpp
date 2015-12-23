#include "Scene/NoState/Ending.h"
#include "GameLib/Framework.h"
#include "Controller/NoState.h"
#include "Controller/Game.h"
#include "Constants.h"

namespace Scene
{

namespace NoState
{

const Controller::NoState::SceneName Ending::Name_ = Controller::NoState::SceneEnding;

Ending::Ending()
{
	new_background_image("data/image/ending.dds");
}

Ending::~Ending()
{
	delete_background_image();
}

Controller::NoState::SceneName Ending::name() const { return Name_; }

void Ending::update(	Controller::NoState::SceneName* next_scene_name,
						Constants::PlayMode*)
{
	if (GameLib::Framework::instance().isKeyTriggered(' '))
	{
		*next_scene_name = Controller::NoState::SceneTitle;
	}

	GameLib::Framework::instance().drawDebugString(0, 0, "[ENDING]", 0xffffffff);
	GameLib::Framework::instance().drawDebugString(0, 1, "... finish the game ..", 0xffffffff);
	GameLib::Framework::instance().drawDebugString(0, 2, "Space to return to TITLE.", 0xffffffff);
	
	draw_background_image();
}

} // namespace NoState

} // namespace Scene
