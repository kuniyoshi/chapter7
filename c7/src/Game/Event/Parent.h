#ifndef BAKUDAN_GAME_EVENT_PARENT_H_
#define BAKUDAN_GAME_EVENT_PARENT_H_

namespace Game
{

namespace Event
{

class Parent
{
private:
	unsigned last_stamp_;
	bool is_pausing_;

public:
	Parent();
	Parent(unsigned last_stamp);
	virtual ~Parent();
	unsigned last_stamp() const;
	void last_stamp(unsigned now);
	virtual bool is_pausing() const;
	virtual void pause(unsigned now);
	virtual void resume(unsigned now);
	virtual void tick(unsigned now) = 0;
};

} // namespace Event

} // namespace Game

#endif
