#ifndef BAKUDAN_ITERATOR_LOOP_H_
#define BAKUDAN_ITERATOR_LOOP_H_

namespace Iterator
{

class Loop
{
private:
	int index_;
	int min_;
	int max_;
	bool did_loop_;

public:
	Loop(int min, int max);
	Loop(int index, int min, int max);
	~Loop();
	operator int() const;
	Loop& operator++();
	Loop& operator--();
	int min() const;
	int max() const;
	void set_min_max(int min, int max);
	bool did_loop() const;
	int unbiased_index() const;
};

} // namespace Iterator

#endif
