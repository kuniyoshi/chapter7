#include "Image/Dds.h"
#include "GameLib/GameLib.h"
#include "Image/functions.h"
#include "File.h"
#include "Point.h"
#include "Size.h"
#include "Iterator/Image.h"

namespace Image
{

Dds::Dds(const File& image_file)
: size_(0), data_(0)
{
	STRONG_ASSERT(image_file.data());
	Size* size_candidate = new Size(0, 0);
	read_dds_size(image_file, size_candidate);
	size_ = size_candidate;

	unsigned* data_candidate = new unsigned[size_->max_index()];
	read_dds_data(image_file, *size_, data_candidate);
	data_ = data_candidate;
}

Dds::~Dds()
{
	SAFE_DELETE_ARRAY(data_);
	SAFE_DELETE(size_);
}

const unsigned Dds::operator[](int index) const
{
	ASSERT(size_->is_index_in(index));
	return data_[index];
}

void Dds::copy(const Point& point, const Size& size, unsigned** vram) const
{
	Point top_left = Point(0, 0);
	Point bottom_right = Point(size_->width() - 1, size_->height() - 1);
	Iterator::Image source_iterator(top_left, bottom_right, *size_);
	Iterator::Image destination_iterator(top_left + point, bottom_right + point, size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			(*vram)[destination_iterator] = data_[source_iterator];
		}

		++source_iterator;
		++destination_iterator;
	}

	int lasts = source_iterator;
	int lastd = destination_iterator;
}

void Dds::copy_alpha_blend(const Point& point, const Size& size, unsigned** vram) const
{
	Point top_left = Point(0, 0);
	Point bottom_right = Point(size_->width() - 1, size_->height() - 1);
	Iterator::Image source_iterator(top_left, bottom_right, *size_);
	Iterator::Image destination_iterator(top_left + point, bottom_right + point, size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			(*vram)[destination_iterator] = alpha_blend(	data_[source_iterator],
															(*vram)[destination_iterator]);
		}

		++source_iterator;
		++destination_iterator;
	}
}

} // namespace Image
