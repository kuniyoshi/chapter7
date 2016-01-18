#include "Sprite.h"
#include "GameLib/GameLib.h"
#include "Game/Event/Move.h"
#include "File.h"
#include "Image/functions.h"
#include "Iterator/Image.h"
#include "Point.h"
#include "Rect.h"
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

const Size& Sprite::size() const { return *size_; }
const Size& Sprite::cell_size() const { return *cell_size_; }
const unsigned* Sprite::data() const { return data_; }

int Sprite::cells_per_column() const { return cells_per_column_; }

namespace
{

Point get_point_from_cell_index(int index, const Size& size, int width)
{
	return Point(	(index % width) * size.width(),
					(index / width) * size.height());
}

void copy_alpha_blend_additional_alpha(	const Sprite& image,
										int index,
										double alpha,
										const Point& point,
										const Size& size,
										unsigned* vram)
{
	const Size& source_size = image.size();
	const Size& cell_size = image.cell_size();
	const unsigned* data = image.data();
	int cells_per_column = image.cells_per_column();

	Point source_top_left = get_point_from_cell_index(	index,
														cell_size,
														cells_per_column);
	Point source_bottom_right(	source_top_left,
								cell_size.width() - 1,
								cell_size.height() - 1);
	Point destination_top_left(	point.x() * cell_size.width(),
								point.y() * cell_size.height());
	Point destination_bottom_right(	destination_top_left,
									cell_size.width() - 1,
									cell_size.height() - 1);

	Iterator::Image source_iterator(	source_top_left,
										source_bottom_right,
										source_size);
	Iterator::Image destination_iterator(	destination_top_left,
											destination_bottom_right,
											size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			vram[destination_iterator] = alpha_blend(	data[source_iterator],
														vram[destination_iterator],
														alpha);
		}

		++source_iterator;
		++destination_iterator;
	}
}

void copy_alpha_blend_additional_alpha(	const Sprite& image,
										int index,
										double alpha,
										const Game::Event::Move& event,
										const Size& size,
										unsigned* vram)
{
	const Size& source_size = image.size();
	const Size& cell_size = image.cell_size();
	const unsigned* data = image.data();
	int cells_per_column = image.cells_per_column();

	Point source_top_left = get_point_from_cell_index(	index,
														cell_size,
														cells_per_column);
	Point source_bottom_right(	source_top_left,
								cell_size.width() - 1,
								cell_size.height() - 1);

	double rate = event.completion_rate();

	Point destination_top_left(	Point(	event.point().x() * cell_size.width(),
										event.point().y() * cell_size.height()),
								static_cast< int >(event.dx() * cell_size.width() * rate),
								static_cast< int >(event.dy() * cell_size.height() * rate));
	Point destination_bottom_right(	destination_top_left,
									cell_size.width() - 1,
									cell_size.height() - 1);

	Iterator::Image source_iterator(	source_top_left,
										source_bottom_right,
										source_size);
	Iterator::Image destination_iterator(	destination_top_left,
											destination_bottom_right,
											size);

	while (source_iterator.has_next())
	{
		if (size.is_iterator_in(destination_iterator))
		{
			vram[destination_iterator] = alpha_blend(	data[source_iterator],
														vram[destination_iterator],
														alpha);
		}

		++source_iterator;
		++destination_iterator;
	}
}

} // namespace -

void Sprite::copy(	int index,
					const Point& point,
					const Size& size,
					unsigned* vram) const
{
	copy_alpha_blend_additional_alpha(*this, index, 0.0, point, size, vram);
}

void Sprite::copy(	int index,
					const Game::Event::Move& event,
					const Size& size,
					unsigned* vram) const
{
	copy_alpha_blend_additional_alpha(*this, index, 0.0, event, size, vram);
}

void Sprite::copy_alpha_blend(	int index,
								double alpha,
								const Point& point,
								const Size& size,
								unsigned* vram) const
{
	copy_alpha_blend_additional_alpha(*this, index, alpha, point, size, vram);
}

void Sprite::copy_alpha_blend(	int index,
								const Point& point,
								const Size& size,
								unsigned* vram) const
{
	copy_alpha_blend_additional_alpha(*this, index, 0.0, point, size, vram);
}


void Sprite::copy_alpha_blend(	int index,
								double alpha,
								const Game::Event::Move& event,
								const Size& size,
								unsigned* vram) const
{
	copy_alpha_blend_additional_alpha(*this, index, alpha, event, size, vram);
}

void Sprite::copy_alpha_blend(	int index,
								const Game::Event::Move& event,
								const Size& size,
								unsigned* vram) const
{
	copy_alpha_blend_additional_alpha(*this, index, 0.0, event, size, vram);
}

int Sprite::cell_width() const { return cell_size_->width(); }
int Sprite::cell_height() const { return cell_size_->height(); }

void Sprite::set_inner_area_of(int index, Rect< double >* rect) const
{
	Point top_left = get_point_from_cell_index(index, *cell_size_, cells_per_column_);
	Point bottom_right(top_left, cell_size_->width() - 1, cell_size_->height() - 1);
	Iterator::Image iterator(top_left, bottom_right, *size_);

	int min_x = iterator.width();
	int max_x = 0;
	int min_y = iterator.height();
	int max_y = 0;

	while (iterator.has_next())
	{
		unsigned alpha = data_[iterator] & 0xff000000;

		if (alpha > 127)
		{
			if (iterator.unbiased_x() > max_x)
			{
				max_x = iterator.unbiased_x();
			}
			if (iterator.unbiased_x() < min_x)
			{
				min_x = iterator.unbiased_x();
			}
			if (iterator.unbiased_y() > max_y)
			{
				max_y = iterator.unbiased_y();
			}
			if (iterator.unbiased_y() < min_y)
			{
				min_y = iterator.unbiased_y();
			}
		}

		++iterator;
	}

	rect->left(static_cast< double >(min_x) / iterator.width());
	rect->right(static_cast< double >(max_x) / iterator.width());
	rect->top(static_cast< double >(min_y) / iterator.height());
	rect->bottom(static_cast< double >(max_y) / iterator.height());
}

} // namespace Image
