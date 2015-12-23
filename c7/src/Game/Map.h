#ifndef BAKUDAN_GAME_MAP_H_
#define BAKUDAN_GAME_MAP_H_

#include "Array2D.h"
#include "State.h"

namespace Image
{

class Sprite;

} // namespace Image

namespace Game
{

class Map
{
private:
	Array2D< State::ObjectImage > cells_;
	int width_;
	int height_;

public:
	Map(int width, int height);
	// ~Map();
	void load();
	void draw(const Image::Sprite& image) const;
};

} // namespace Game

#endif
