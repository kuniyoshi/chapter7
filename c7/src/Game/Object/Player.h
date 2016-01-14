#ifndef BAKUDAN_GAME_OBJECT_PLAYER_H
#define BAKUDAN_GAME_OBJECT_PLAYER_H
#include "Game/Object/Parent.h"
#include "Rect.h"

namespace Image { class Sprite; }

class Point;
class Piece;

namespace Game { namespace Event { class Move; } }

namespace Game
{

namespace Object
{

class Player : public Parent
{
private:
	int player_index_;
	Event::Move* move_event_;
	Rect< double > rect_;
	unsigned ms_to_collision_;
	bool will_stop_;
	bool is_stopping_;

public:
	Player(int index, const Point& point, const Image::Sprite& image);
	virtual ~Player();
	virtual void ms_to_collision(unsigned new_value);
	virtual bool is_stopping() const;
	virtual void clear_volatility_condition();
	virtual void move_to(const Point& new_point, unsigned now);
	virtual void tick(unsigned now);
	virtual void draw(const Image::Sprite& image) const;
	virtual void pause(unsigned now);
	virtual void resume(unsigned now);
	virtual void stop_until(unsigned ms);
	virtual Piece make_piece() const;
	virtual Point current_point() const;
	virtual bool does_direction_open(const Player& other, unsigned ms) const;
};

} // namespace Object

} // namespace Game

#endif
