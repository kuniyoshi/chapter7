#include "Scene/NoState/Title.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Controller/NoState.h"
#include "Game/InputManager.h"
#include "Iterator/Loop.h"

namespace Scene
{

namespace NoState
{

const Controller::NoState::SceneName Title::Name_ = Controller::NoState::SceneTitle;

Title::Title()
: looped_index_(Iterator::Loop(0, 1))
{
    new_background_image("data/image/title.dds");
}

Title::~Title()
{
    delete_background_image();
}

Controller::NoState::SceneName Title::name() const { return Name_; }

void Title::update( Controller::NoState::SceneName* next_scene_name,
                    Constants::PlayMode* play_mode)
{
    const Constants::PlayMode modes[]
    = {Constants::PlayMode1P, Constants::PlayMode2P};

    GameLib::Framework f = GameLib::Framework::instance();

    ::Game::InputManager user1_input = ::Game::InputManager::user1();

    if (user1_input.is_option())
    {
        *next_scene_name = Controller::NoState::SceneGame;
        *play_mode = modes[looped_index_];
    }
    else if (user1_input.is_top_triggered())
    {
        ++looped_index_;
    }
    else if (user1_input.is_bottom_triggered())
    {
        --looped_index_;
    }

    f.drawDebugString(0, 0, "[TITLE]", 0xffffffff);
    f.drawDebugString(1, 1, "1P Mode", 0xffffffff);
    f.drawDebugString(1, 2, "2P Mode", 0xffffffff);
    f.drawDebugString(0, looped_index_ + 1, ">", 0xffffffff);
}

} // namespace NoState

} // namespace Scene
