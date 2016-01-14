#ifndef BAKUDAN_GAME_MAP_H_
#define BAKUDAN_GAME_MAP_H_

#include "Array2D.h"
#include "State.h"

class Point;

namespace Image
{

class Sprite;

} // namespace Image

namespace Game
{

class Map
{
private:
	Array2D< State::ObjectImage > background_cells_;
	Array2D< State::ObjectImage > foreground_cells_;
	int width_;
	int height_;

public:
	Map(int width, int height);
	// ~Map();
	void load();
	void draw(const Image::Sprite& image) const;
	bool can_not_invade(int x, int y) const;
	bool can_not_invade(const Point& point) const;
};

} // namespace Game

#endif
