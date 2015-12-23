#ifndef BAKUDAN_SIZE_H_
#define BAKUDAN_SIZE_H_

namespace Iterator
{

class Image;

} // namespace Iterator

class Size
{
private:
	int width_;
	int height_;

public:
	Size(int width, int height);
	Size();
	~Size();
	int width() const;
	int height() const;
	int max_index() const;
	bool is_index_in(int x, int y) const;
	bool is_index_in(int index) const;
	void set_width_height(int width, int height);
	bool is_iterator_in(const Iterator::Image& iterator) const;
};

#endif
