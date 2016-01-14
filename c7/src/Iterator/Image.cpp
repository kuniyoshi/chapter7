#include "Iterator/Image.h"
#include "Point.h"
#include "Size.h"
#include "Iterator/Loop.h"

namespace Iterator
{

Image::Image(const Point& from, const Point& to, const Size& size)
:	from_(from), to_(to),
	width_(size.width()),
	loop_x_(Loop(from.x(), to.x())), loop_y_(Loop(from.y(), to.y()))
{}

Image::~Image() {}

Image& Image::operator++()
{
	++loop_x_;

	if (loop_x_.did_loop())
	{
		++loop_y_;
	}

	return *this;
}

Image::operator int() const
{
	return loop_y_ * width_ + loop_x_;
}

bool Image::has_next() const { return !loop_y_.did_loop(); }

int Image::width() const { return loop_x_.max() - loop_x_.min(); }
int Image::height() const { return loop_y_.max() - loop_y_.min(); }

int Image::unbiased_x() const { return loop_x_.unbiased_index(); }
int Image::unbiased_y() const { return loop_y_.unbiased_index(); }

} // namespace Iterator
