#ifndef BAKUDAN_SCENE_PARENT_H_
#define BAKUDAN_SCENE_PARENT_H_

namespace Image
{

class Dds;

} // namespace Image

namespace Scene
{

class Parent
{
private:
	Image::Dds* image_;

public:
	Parent();
	virtual ~Parent();

	void new_background_image(const char* filename);
	void delete_background_image();
	void draw_background_image() const;
};

} // namespace Scene

#endif
