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
	cells_.set_size(width_, height_);
}

void Map::load()
{
	for (int y = 0; y < height_; ++y)
	{
		for (int x = 0; x < width_; ++x)
		{
			cells_(x, y) = (y == 0 || y == height_ - 1 || x == 0 || x == width_ - 1)
				? State::OBJECT_IMAGE_BLOCK
				: (!(y % 2) && !(x % 2))
				? State::OBJECT_IMAGE_BLOCK
				: State::OBJECT_IMAGE_FLOOR;
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
			image.copy(	cells_(x, y),
						Point(x, y),
						size,
						vram);
		}
	}
}

bool Map::is_block(int x, int y) const
{
	return cells_(x, y) == State::OBJECT_IMAGE_BLOCK;
}

bool Map::is_block(const Point& point) const
{
	return cells_(point.x(), point.y()) == State::OBJECT_IMAGE_BLOCK;
}

} // namespace Game
