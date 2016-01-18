#include "Game/Ai/RuleBase.h"
#include "GameLib/Framework.h"
#include "Game/Map.h"
#include "Game/Object/Enemy.h"
#include "Point.h"

namespace Game
{

namespace Ai
{

namespace
{

const int MaxRate = 100;
const Point Directions[] = {	Point(-1, 0),
								Point(1, 0),
								Point(0, -1),
								Point(0, 1)};

} // namespace -

namespace
{

void normalize_rate(int* direction_rates_)
{
	int sum = 0;
	int* p_to_max = &direction_rates_[0];

	for (int i = 0; i < 4; ++i)
	{
		sum = sum + direction_rates_[i];

		if (direction_rates_[i] > *p_to_max)
		{
			p_to_max = &direction_rates_[i];
		}
	}

	if (sum == 0)
	{
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		direction_rates_[i] = MaxRate * direction_rates_[i] / sum;
	}

	int new_sum = 0;

	for (int i = 0; i < 4; ++i)
	{
		new_sum = new_sum + direction_rates_[i];
	}

	*p_to_max = *p_to_max + (MaxRate - (new_sum));
}

} // namespace -

RuleBase::RuleBase(	int direction_rate_left,
					int direction_rate_right,
					int direction_rate_top,
					int direction_rate_bottom,
					int reverse_rate_at_moving)
: reverse_rate_at_moving_(reverse_rate_at_moving)
{
	direction_rates_[0] = direction_rate_left,
	direction_rates_[1] = direction_rate_right,
	direction_rates_[2] = direction_rate_top,
	direction_rates_[3] = direction_rate_bottom,

	normalize_rate(direction_rates_);
}

bool RuleBase::can_reverse_direction(	const Object::Enemy& self,
										int friends_size,
										const Object::Enemy* friends,
										int self_index) const
{
	for (int i = 0; i < friends_size; ++i)
	{
		if (i == self_index)
		{
			continue;
		}

		if (friends[i].point() == self.point())
		{
			return false;
		}
	}

	GameLib::Framework f = GameLib::Framework::instance();

	return f.getRandom(MaxRate) < reverse_rate_at_moving_;
}

bool RuleBase::can_start_moving(	const Object::Enemy& self,
									int friends_size,
									const Object::Enemy* friends,
									int self_index) const
{
	for (int i = 0; i < friends_size; ++i)
	{
		if (i == self_index)
		{
			continue;
		}

		if (friends[i].point() == self.point())
		{
			return false;
		}

		if (friends[i].current_point() == self.point())
		{
			return false;
		}
	}

	return true;
}

Point RuleBase::select_direction(	const Object::Enemy& self,
									const Map& map,
									int friends_size,
									const Object::Enemy* friends,
									int self_index)
{
	int rates[4];
	Point next_candidates[4];

	// do not change the original
	for (int i = 0; i < 4; ++i)
	{
		rates[i] = direction_rates_[i];
	}

	for (int i = 0; i < 4; ++i)
	{
		next_candidates[i] = self.point() + Directions[i];

		if (map.can_not_invade(next_candidates[i]))
		{
			rates[i] = 0;
		}
	}

	for (int i = 0; i < friends_size; ++i)
	{
		if (i == self_index)
		{
			continue;
		}

		if (friends[i].point() == next_candidates[i])
		{
			rates[i] = 0;
		}
		else if (friends[i].current_point() == next_candidates[i])
		{
			rates[i] = 0;
		}
	}
	
	normalize_rate(rates);

	if ((rates[0] + rates[1] + rates[2] + rates[3]) == 0)
	{
		return Point(0, 0);
	}

	GameLib::Framework f = GameLib::Framework::instance();

	int rate = f.getRandom(MaxRate);
	int index = 0;
	int sum = 0;

	for (int i = 0; i < 4; ++i)
	{
		sum = sum + rates[i];

		if (sum > rate)
		{
			index = i;
			break;
		}
	}

	return Directions[index];
}

} // namespace Ai

} // namespace Game
