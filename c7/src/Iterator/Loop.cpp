#include "Iterator/Loop.h"

namespace Iterator
{

Loop::Loop(int min, int max)
: index_(min), min_(min), max_(max), did_loop_(false)
{}

Loop::Loop(int index, int min, int max)
: index_(index), min_(min), max_(max), did_loop_(false)
{}

Loop::~Loop() {}

Loop::operator int() const { return index_; }

Loop& Loop::operator++()
{
	++index_;
	if (index_ > max_)
	{
		index_ = min_;
		did_loop_ = true;
	}
	else
	{
		did_loop_ = false;
	}
	return *this;
}

Loop& Loop::operator--()
{
	--index_;
	if (index_ < min_)
	{
		index_ = max_;
		did_loop_ = true;
	}
	else
	{
		did_loop_ = false;
	}
	return *this;
}

int Loop::min() const { return min_; }
int Loop::max() const { return max_; }

void Loop::set_min_max(int min, int max)
{
	min_ = min;
	max_ = max;
}

bool Loop::did_loop() const { return did_loop_; }

int Loop::unbiased_index() const { return index_ - min_; }

} // namespace Iterator
