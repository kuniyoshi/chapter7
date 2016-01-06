#ifndef BAKUDAN_GAME_OBJECT_PLAYER_H
#define BAKUDAN_GAME_OBJECT_PLAYER_H
#include "Game/Object/Parent.h"

namespace Image
{

class Sprite;

} // namespace Image

class Point;

namespace Game
{

namespace Event
{

class Move;

} // namespace Event

namespace Object
{

class Player : public Parent
{
private:
	int player_index_;
	Event::Move* move_event_;

public:
	Player(int index, const Point& point);
	virtual ~Player();
	virtual void move_to(const Point& new_point, unsigned now);
	virtual void tick(unsigned now);
	virtual void draw(const Image::Sprite& image) const;
	virtual void pause(unsigned now);
	virtual void resume(unsigned now);
};

} // namespace Object

} // namespace Game

#endif
