#include "Scene/NoState/GameOver.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Controller/NoState.h"
#include "Game/InputManager.h"

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

void GameOver::update(  Controller::NoState::SceneName* next_scene_name,
                        Constants::PlayMode*)
{
    if (::Game::InputManager::user1().is_option())
    {
        *next_scene_name = Controller::NoState::SceneTitle;
    }
    
    GameLib::Framework::instance().drawDebugString(0, 0, "[GAME OVER]", 0xffffffff);
}

} // namespace NoState

} // namespace Scene
