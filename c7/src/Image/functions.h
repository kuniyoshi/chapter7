#ifndef BAKUDAN_IMAGE_FUNCTIONS_H_
#define BAKUDAN_IMAGE_FUNCTIONS_H_

class Size;
class File;

namespace Image
{

void read_dds_size(const File& image_file, Size* size);
void read_dds_data(const File& image_file, const Size& size, unsigned* data);
unsigned alpha_blend(unsigned upper, unsigned base);
unsigned alpha_blend(unsigned upper, unsigned base, double alpha);

} // namespace Image

#endif
