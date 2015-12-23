#ifndef BAKUDAN_STATE_H_
#define BAKUDAN_STATE_H_

#include "Controller/Game.h"
#include "Constants.h"

namespace Image
{

class Sprite;

} // namespace Image

namespace Game
{

class Map;
// class Object;

} // namespace Game

class State
{
public:
	enum ObjectImage
	{
		OBJECT_IMAGE_PLAYER1 = 0,
		OBJECT_IMAGE_PLAYER2,
		OBJECT_IMAGE_BOMB_ITEM,
		OBJECT_IMAGE_SOTRM_ITEM,
		OBJECT_IMAGE_HORIZONTAL_STORM,
		OBJECT_IMAGE_VERTICAL_STORM,
		OBJECT_IMAGE_ENEMY,
		OBJECT_IMAGE_BLOCK,
		OBJECT_IMAGE_WALL,
		OBJECT_IMAGE_FLOOR,
		OBJECT_IMAGE_BOMB,
		OBJECT_IMAGE_CROSS_STORM,
		OBJECT_IMAGE_BURNING_WALL = 12,
	};

private:
	Image::Sprite* object_image_;
	Game::Map* map_;
	// Game::Object* objects_;

public:
	State();
	~State();
	void load(Constants::PlayMode play_mode);
	void draw() const;
};

#endif
