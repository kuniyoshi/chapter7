#include "Scene/NoState/GameOver.h"
#include "GameLib/Framework.h"
#include "Controller/NoState.h"
#include "Controller/Game.h"
#include "Constants.h"

namespace Scene
{

namespace NoState
{

const Controller::NoState::SceneName GameOver::Name_
= Controller::NoState::SceneGameOver;

GameOver::GameOver()
{
	new_background_image("data/image/game_over.dds");
}

GameOver::~GameOver()
{
	delete_background_image();
}

Controller::NoState::SceneName GameOver::name() const { return Name_; }

void GameOver::update(	Controller::NoState::SceneName* next_scene_name,
						Constants::PlayMode*)
{
	if (GameLib::Framework::instance().isKeyTriggered(' '))
	{
		*next_scene_name = Controller::NoState::SceneTitle;
	}
	
	GameLib::Framework::instance().drawDebugString(0, 0, "[GAME OVER]", 0xffffffff);

	draw_background_image();
}

} // namespace NoState

} // namespace Scene
