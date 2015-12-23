#include "Size.h"
#include "Iterator/Image.h"

Size::Size(int width, int height)
: width_(width), height_(height)
{}
Size::Size()
: width_(0), height_(0)
{}

Size::~Size() {}

int Size::width() const { return width_; }
int Size::height() const { return height_; }
int Size::max_index() const { return width_ * height_; }
bool Size::is_index_in(int x, int y) const
{
	return	x >= 0
			&& x <= width_
			&& y >= 0
			&& y <= height_;
}
bool Size::is_index_in(int index) const
{
	return index >= 0 && index < width_ * height_;
}
void Size::set_width_height(int width, int height)
{
	width_ = width;
	height_ = height;
}
bool Size::is_iterator_in(const Iterator::Image& iterator) const
{
	return is_index_in(iterator.width(), iterator.height());
}