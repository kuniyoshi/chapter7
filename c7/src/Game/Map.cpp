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
			cells_(x, y) = (y == 0 || x == 0)
				? State::OBJECT_IMAGE_BLOCK
				: ((y % 2) && x == y)
				? State::OBJECT_IMAGE_BLOCK
				: State::OBJECT_IMAGE_WALL;
		}
	}
}

void Map::draw(const Image::Sprite& image) const
{
	GameLib::Framework f = GameLib::Framework::instance();
	Size size(f.width(), f.height());
	unsigned* vram = f.videoMemory();
	int width = image.cell_width();
	int height = image.cell_height();

	for (int y = 0; y < height_; ++y)
	{
		for (int x = 0; x < width_; ++x)
		{
			image.copy(	cells_(x, y),
						Point(x * width, y * height),
						size,
						vram);
		}
	}
}

} // namespace Game
