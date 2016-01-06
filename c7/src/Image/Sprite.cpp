#include "Sprite.h"
#include "GameLib/GameLib.h"
#include "Game/Event/Move.h"
#include "File.h"
#include "Image/functions.h"
#include "Iterator/Image.h"
#include "Point.h"
#include "Size.h"

namespace Image
{

Sprite::Sprite(const File& image_file, int column_count, int row_count)
: size_(0), cell_size_(0), data_(0),
cells_per_column_(column_count), cells_per_row_(row_count)
{
	Size* size_candidate = new Size();
	read_dds_size(image_file, size_candidate);
	size_ = size_candidate;

	cell_size_ = new Size(size_->width() / column_count, size_->height() / row_count);

	unsigned* data_candidate = new unsigned[size_->max_index()];
	read_dds_data(image_file, *size_, data_candidate);
	data_ = data_candidate;
}

Sprite::~Sprite()
{
	SAFE_DELETE(size_);
	SAFE_DELETE(cell_size_);
	SAFE_DELETE(data_);
}

namespace
{

Point get_point_from_cell_index(int index, const Size& size, int width)
{
	return Point(	(index % width) * size.width(),
					(index / width) * size.height());
}

} // namespace -

void Sprite::copy(	int index,
					const Point& point,
					const Size& size,
					unsigned* vram) const
{
	Point source_top_left
	= get_point_from_cell_index(index, *cell_size_, cells_per_column_);
	Point source_bottom_right(	source_top_left,
								cell_size_->width() - 1,
								cell_size_->height() - 1);
	Point destination_top_left(	point.x() * cell_size_->width(),
								point.y() * cell_size_->height());
	Point destination_bottom_right(	destination_top_left,
									cell_size_->width() - 1,
									cell_size_->height() - 1);

	Iterator::Image source_iterator(	source_top_left,
										source_bottom_right,
										*size_);
	Iterator::Image destination_iterator(	destination_top_left,
											destination_bottom_right,
											size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			vram[destination_iterator] = data_[source_iterator];
		}
		
		++source_iterator;
		++destination_iterator;
	}
}

void Sprite::copy(	int index,
					const Game::Event::Move& event,
					const Size& size,
					unsigned* vram) const
{
	Point source_top_left
	= get_point_from_cell_index(index, *cell_size_, cells_per_column_);
	Point source_bottom_right(	source_top_left,
								cell_size_->width() - 1,
								cell_size_->height() - 1);

	double rate = event.completion_rate();
	Point destination_top_left(	Point(	event.point(),
										cell_size_->width() - 1,
										cell_size_->height() - 1),
								static_cast< int >(event.dx() * cell_size_->width() * rate),
								static_cast< int >(event.dy() * cell_size_->height() * rate));
	Point destination_bottom_right(	destination_top_left,
									cell_size_->width() - 1,
									cell_size_->height() - 1);

	Iterator::Image source_iterator(	source_top_left,
										source_bottom_right,
										*size_);
	Iterator::Image destination_iterator(	destination_top_left,
											destination_bottom_right,
											size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			vram[destination_iterator] = data_[source_iterator];
		}

		++source_iterator;
		++destination_iterator;
	}
}

void Sprite::copy_alpha_blend(	int index,
								const Point& point,
								const Size& size,
								unsigned* vram) const
{
	Point source_top_left
	= get_point_from_cell_index(index, *cell_size_, cells_per_column_);
	Point source_bottom_right(	source_top_left,
								cell_size_->width() - 1,
								cell_size_->height() - 1);
	Point destination_top_left(	point.x() * cell_size_->width(),
								point.y() * cell_size_->height());
	Point destination_bottom_right(	destination_top_left,
									cell_size_->width() - 1,
									cell_size_->height() - 1);

	Iterator::Image source_iterator(	source_top_left,
										source_bottom_right,
										*size_);
	Iterator::Image destination_iterator(	destination_top_left,
											destination_bottom_right,
											size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			vram[destination_iterator] = alpha_blend(	data_[source_iterator],
														vram[destination_iterator]);
		}

		++source_iterator;
		++destination_iterator;
	}
}

void Sprite::copy_alpha_blend(	int index,
								const Game::Event::Move& event,
								const Size& size,
								unsigned* vram) const
{
	Point source_top_left
	= get_point_from_cell_index(index, *cell_size_, cells_per_column_);
	Point source_bottom_right(	source_top_left,
								cell_size_->width() - 1,
								cell_size_->height() - 1);

	double rate = event.completion_rate();

	Point destination_top_left(	Point(	event.point().x() * cell_size_->width(),
										event.point().y() * cell_size_->height()),
								static_cast< int >(event.dx() * cell_size_->width() * rate),
								static_cast< int >(event.dy() * cell_size_->height() * rate));
	Point destination_bottom_right(	destination_top_left,
									cell_size_->width() - 1,
									cell_size_->height() - 1);

	Iterator::Image source_iterator(	source_top_left,
										source_bottom_right,
										*size_);
	Iterator::Image destination_iterator(	destination_top_left,
											destination_bottom_right,
											size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			vram[destination_iterator] = alpha_blend(	data_[source_iterator],
														vram[destination_iterator]);
		}

		++source_iterator;
		++destination_iterator;
	}
}

int Sprite::cell_width() const { return cell_size_->width(); }
int Sprite::cell_height() const { return cell_size_->height(); }

} // namespace Image
