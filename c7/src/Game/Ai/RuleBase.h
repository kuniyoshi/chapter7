#ifndef BAKUDAN_GAME_AI_RULE_BASE_H_
#define BAKUDAN_GAME_AI_RULE_BASE_H_

class Point;
namespace Game { class Map; }
namespace Game { namespace Object { class Enemy; } }

namespace Game
{

namespace Ai
{

class RuleBase
{
private:
	int direction_rates_[4];
	int reverse_rate_at_moving_;

public:
	RuleBase(	int direction_rate_left,
				int direction_rate_right,
				int direction_rate_top,
				int direction_rate_bottom,
				int reverse_rate_at_moving);
	bool can_reverse_direction(	const Object::Enemy& self,
								int friends_size,
								const Object::Enemy* friends,
								int self_index) const;
	bool can_start_moving(	const Object::Enemy& self,
							int friends_size,
							const Object::Enemy* friends,
							int self_index) const;
	Point select_direction(	const Object::Enemy& self,
							const Map& map,
							int friends_size,
							const Object::Enemy* friends,
							int self_index);
};

} // namespace Ai

} // namespace Game

#endif
