#ifndef BAKUDAN_GAME_OBJECT_PARENT_H_
#define BAKUDAN_GAME_OBJECT_PARENT_H_
#include "Point.h"

namespace Image
{

class Sprite;

} // namespace Image

namespace Game
{

namespace Object
{

class Parent
{
private:
	Point point_;
	bool did_die_;

public:
	Parent();
	Parent(const Point& point);
	virtual ~Parent();
	const Point& point() const;
	void point(const Point& new_point);
	virtual bool did_die() const;
	virtual void did_die(bool new_value);
	virtual void tick(unsigned now) = 0;
	virtual void draw(const Image::Sprite& image) const = 0;
};

} // namespace Object

} // namespace Game

#endif
