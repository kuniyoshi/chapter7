#include "State.h"
#include "GameLib/Framework.h"
#include "File.h"
#include "Image/Sprite.h"
#include "Game/Map.h"
// #include "Game/Object.h"
#include "Constants.h"

State::State()
: object_image_(0), map_(0)
// : object_image_(0), map_(0), objects_(0)
{
	// load object_image_ later
	map_ = new Game::Map(19, 15);
}

State::~State()
{
	SAFE_DELETE(object_image_);
	SAFE_DELETE(map_);
	// SAFE_DELETE(objects_);
}

void State::load(Constants::PlayMode)
{
	ASSERT(!object_image_);
	object_image_ = new Image::Sprite(File("data/image/BakudanBitoImage.dds"), 4, 4);
	map_->load();
}

void State::draw() const
{
	map_->draw(*object_image_);
}
