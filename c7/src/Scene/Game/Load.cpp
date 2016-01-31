#include "Scene/Game/Load.h"
#include "GameLib/Framework.h"
#include "Controller/Game.h"
#include "State.h"
#include "Constants.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName Load::Name_ = Controller::Game::SceneLoad;

Load::Load()
: play_mode_(Constants::PlayMode1P), did_start_loading_(false)
{
	new_background_image("data/image/game/load.dss");
}

Load::Load(Constants::PlayMode play_mode)
: play_mode_(play_mode), did_start_loading_(false)
{
	new_background_image("data/image/game/load.dds");
}

Load::~Load() { delete_background_image(); }

Controller::Game::SceneName Load::name() const { return Name_; }

void Load::update(State* state, Controller::Game::SceneName* next_scene_name)
{
	if (!did_start_loading_)
	{
		did_start_loading_ = true;
		state->load(play_mode_);
		*next_scene_name = Controller::Game::ScenePlay;
	}
}

} // namespace Game

} // namespace Scene
