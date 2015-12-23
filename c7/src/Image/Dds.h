#ifndef BAKUDAN_IMAGE_DDS_H_
#define BAKUDAN_IMAGE_DDS_H_

class File;
class Point;
class Size;

namespace Image
{

class Dds
{
private:
	const Size* size_;
	const unsigned* data_;

public:
	Dds(const File& image_file);
	~Dds();
	const unsigned operator[](int index) const;
	void copy(const Point& point, const Size& size, unsigned* vram) const;
	void copy_alpha_blend(const Point& point, const Size& size, unsigned* vram) const;
};

} // namespace Image

#endif
