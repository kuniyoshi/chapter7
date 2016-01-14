#include "Game/Map.h"
#include "GameLib/Framework.h"
#include "Image/Sprite.h"
#include "State.h"
#include "Point.h"
#include "Size.h"

namespace Game
{

Map::Map(int width, int height)
: width_(width), height_(height)
{
	background_cells_.set_size(width_, height_);
	foreground_cells_.set_size(width_, height_);
}

void Map::load()
{
	for (int y = 0; y < height_; ++y)
	{
		for (int x = 0; x < width_; ++x)
		{
			background_cells_(x, y) = (y == 0 || y == height_ - 1 || x == 0 || x == width_ - 1)
				? State::OBJECT_IMAGE_BLOCK
				: (!(y % 2) && !(x % 2))
				? State::OBJECT_IMAGE_BLOCK
				: State::OBJECT_IMAGE_FLOOR;
			foreground_cells_(x, y) = State::OBJECT_IMAGE_NOTHING;
		}
	}
}

void Map::draw(const Image::Sprite& image) const
{
	GameLib::Framework f = GameLib::Framework::instance();
	Size size(f.width(), f.height());
	unsigned* vram = f.videoMemory();

	for (int y = 0; y < height_; ++y)
	{
		for (int x = 0; x < width_; ++x)
		{
			image.copy(	background_cells_(x, y),
						Point(x, y),
						size,
						vram);
		}
	}
}

namespace
{

bool is_block(const Array2D< State::ObjectImage >& cells, int x, int y)
{
	return cells(x, y) == State::OBJECT_IMAGE_BLOCK;
}

bool is_block(const Array2D< State::ObjectImage >& cells, const Point& point)
{
	return cells(point.x(), point.y()) == State::OBJECT_IMAGE_BLOCK;
}

bool is_bomb(const Array2D< State::ObjectImage >& cells, int x, int y)
{
	return cells(x, y) == State::OBJECT_IMAGE_BOMB;
}

bool is_bomb(const Array2D< State::ObjectImage >& cells, const Point& point)
{
	return cells(point.x(), point.y()) == State::OBJECT_IMAGE_BOMB;
}

} // namespace -

bool Map::can_not_invade(int x, int y) const
{
	return is_block(background_cells_, x, y)
		|| is_bomb(foreground_cells_, x, y);
}

bool Map::can_not_invade(const Point& point) const
{
	return is_block(background_cells_, point)
		|| is_bomb(foreground_cells_, point);
}

} // namespace Game
