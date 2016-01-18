#ifndef BAKUDAN_ITERATOR_IMAGE
#define BAKUDAN_ITERATOR_IMAGE

#include "Point.h"
#include "Iterator/Loop.h"

class Size;

namespace Iterator
{

class Image
{
private:
	Point from_;
	Point to_;
	int width_;
	Loop loop_x_;
	Loop loop_y_;
public:
	Image(const Point& from, const Point& to, const Size& size);
	~Image();
	Image& operator++();
	operator int() const;
	bool has_next() const;
	int width() const;
	int height() const;
	int unbiased_x() const;
	int unbiased_y() const;
	void reset();
};

} // namespace Iterator

#endif
