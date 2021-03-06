#include "Scene/Parent.h"
#include "GameLib/Framework.h"
#include "Image/Dds.h"
#include "File.h"
#include "Point.h"
#include "Size.h"

namespace Scene
{

Parent::Parent() {}

Parent::~Parent() { delete_background_image(); }

void Parent::new_background_image(const char* filename)
{
	image_ = new Image::Dds(File(filename));
}

void Parent::delete_background_image()
{
	SAFE_DELETE(image_);
}

} // namespace Scene
