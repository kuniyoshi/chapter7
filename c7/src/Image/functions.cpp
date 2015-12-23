#include "Image/functions.h"
#include "Size.h"
#include "File.h"

namespace Image
{

void read_dds_size(const File& image_file, Size* size)
{
	int width = static_cast< int >(image_file.get_unsigned(16));
	int height = static_cast< int >(image_file.get_unsigned(12));
	size->set_width_height(width, height);
}

void read_dds_data(const File& image_file, const Size& size, unsigned* data)
{
	for (int i = 0; i < size.max_index(); ++i)
	{
		data[i] = image_file.get_unsigned(128 + 4 * i);
	}
}

unsigned alpha_blend(unsigned upper, unsigned base)
{
	unsigned base_r = (base & 0x00ff0000) >> 16;
	unsigned base_g = (base & 0x0000ff00) >> 8;
	unsigned base_b = (base & 0x000000ff) >> 0;
	double alpha = static_cast< double >((upper & 0xff000000) >> 24) / 255.0;
	unsigned upper_r = (upper & 0x00ff0000) >> 16;
	unsigned upper_g = (upper & 0x0000ff00) >> 8;
	unsigned upper_b = (upper & 0x000000ff) >> 0;
	unsigned value = static_cast< unsigned >(alpha * upper_r + (1 - alpha) * base_r) << 16;
	value += static_cast< unsigned >(alpha * upper_g + (1 - alpha) * base_g) << 8;
	value += static_cast< unsigned >(alpha * upper_b + (1 - alpha) * base_b) << 0;
	return value;
}

} // namespace Image
