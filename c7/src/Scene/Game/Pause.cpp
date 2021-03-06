#include "Scene/Game/Pause.h"
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Controller/Game.h"
#include "Game/InputManager.h"
#include "Iterator/Loop.h"
#include "State.h"

namespace Scene
{

namespace Game
{

const Controller::Game::SceneName Pause::Name_ = Controller::Game::ScenePause;

Pause::Pause()
: play_mode_(Constants::PlayMode1P), looped_index_(0, 1)
{}

Pause::Pause(Constants::PlayMode play_mode)
: play_mode_(play_mode), looped_index_(0, 1)
{}

Pause::~Pause() {}

Controller::Game::SceneName Pause::name() const { return Name_; }

void Pause::update(State* state, Controller::Game::SceneName* next_scene_name)
{
    Controller::Game::SceneName next_candidates[]
    = {Controller::Game::SceneNoStateTitle, Controller::Game::ScenePlay};

    GameLib::Framework f = GameLib::Framework::instance();
    f.drawDebugString(0, 0, "Pausing...", 0xffffffff);

    ::Game::InputManager user_input = ::Game::InputManager::user1();

    if (user_input.is_top_triggered())
    {
        --looped_index_;
    }
    else if (user_input.is_bottom_triggered())
    {
        ++looped_index_;
    }

    f.drawDebugString(0, 4, "Select Next Scene", 0xff000000);
    f.drawDebugString(1, 5, "Go to Title", 0xff000000);
    f.drawDebugString(1, 6, "Go back to Play", 0xff000000);
    f.drawDebugString(0, looped_index_ + 5, ">", 0xff000000);

    if (user_input.is_option_triggered())
    {
        *next_scene_name = next_candidates[looped_index_];

        if (next_candidates[looped_index_] == Controller::Game::ScenePlay)
        {
            state->resume();
        }
    }

    state->draw();
}

} // namespace Game

} // namespace Scene
