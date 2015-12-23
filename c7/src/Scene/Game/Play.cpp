#include "Scene/Game/Play.h"
#include "GameLib/Framework.h"
#include "Controller/Game.h"
#include "State.h"
#include "Constants.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName Play::Name_ = Controller::Game::ScenePlay;

Play::Play()
: play_mode_(Constants::PlayMode1P)
{}

Play::Play(Constants::PlayMode play_mode)
: play_mode_(play_mode)
{}

Play::~Play() {}

Controller::Game::SceneName Play::name() const { return Name_; }

void Play::update(State* state, Controller::Game::SceneName* next_scene_name)
{
	GameLib::Framework f = GameLib::Framework::instance();
	f.drawDebugString(0, 0, "NOW YOU ARE PLAYING...");
	state->draw();
}

} // namespace Game

} // namespace Scene
