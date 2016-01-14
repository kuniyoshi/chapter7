#include "Scene/NoState/Title.h"
#include "GameLib/Framework.h"
#include "Controller/NoState.h"
#include "Controller/Game.h"
#include "Iterator/Loop.h"
#include "Constants.h"

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

void Title::update(	Controller::NoState::SceneName* next_scene_name,
					Constants::PlayMode* play_mode)
{
	const Constants::PlayMode modes[]
	= {Constants::PlayMode1P, Constants::PlayMode2P};

	GameLib::Framework f = GameLib::Framework::instance();

	if (f.isKeyTriggered(' '))
	{
		*next_scene_name = Controller::NoState::SceneGame;
		*play_mode = modes[looped_index_];
	}
	else if (f.isKeyTriggered('w'))
	{
		++looped_index_;
	}
	else if (f.isKeyTriggered('z'))
	{
		--looped_index_;
	}

	draw_background_image();

	f.drawDebugString(0, 0, "[TITLE]", 0xffffffff);
	f.drawDebugString(1, 1, "1P Mode", 0xffffffff);
	f.drawDebugString(1, 2, "2P Mode", 0xffffffff);
	f.drawDebugString(0, looped_index_ + 1, ">", 0xffffffff);
}

} // namespace NoState

} // namespace Scene
