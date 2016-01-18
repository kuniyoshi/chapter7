#ifndef BAKUDAN_GAME_OBJECT_PLAYER_H
#define BAKUDAN_GAME_OBJECT_PLAYER_H
#include "Game/Object/Parent.h"
#include "Rect.h"

class Piece;
class Point;
namespace Game { namespace Event { class Dying; } }
namespace Game { namespace Event { class Move; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Object
{

class Player : public Parent
{
private:
	int player_index_;
	Event::Dying* dying_event_;
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
	virtual void prepare();
	virtual void move_to(const Point& new_point, unsigned now);
	virtual void will_die(unsigned now, unsigned ms_to_completion);
	virtual void tick(unsigned now);
	virtual void draw(const Image::Sprite& image) const;
	virtual void pause(unsigned now);
	virtual void resume(unsigned now);
	virtual void stop_after(unsigned ms);
	virtual Piece make_piece() const;
	virtual Point current_point() const;
	virtual bool does_direction_open(const Player& other, unsigned ms) const;
};

} // namespace Object

} // namespace Game

#endif
