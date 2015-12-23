#ifndef BAKUDAN_IMAGE_SPRITE_H_
#define BAKUDAN_IMAGE_SPRITE_H_

class Size;
class File;
class Point;

namespace Image
{

class Sprite 
{
private:
	const Size* size_;
	const Size* cell_size_;
	const unsigned* data_;
	const int cells_per_column_;
	const int cells_per_row_;

public:
	Sprite(const File& image_file, int column_count, int row_count);
	~Sprite();
	void copy(int cell_index, const Point& point, const Size& size, unsigned* vram) const;
	void copy_alpha_blend(int cell_index, const Point& point, const Size& size, unsigned* vram) const;
	int cell_width() const;
	int cell_height() const;
};

} // namespace Image

#endif
