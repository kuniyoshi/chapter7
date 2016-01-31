#include "Game/Object/Wall.h"
#include "GameLib/Framework.h"
#include "Game/Event/Burn.h"
#include "Image/Sprite.h"
#include "Point.h"
#include "Size.h"
#include "State.h"

namespace Game
{

namespace Object
{

Wall::Wall(const Point& point)
: Parent(point), burn_event_(0)
{}

Wall::~Wall()
{
    SAFE_DELETE(burn_event_);
}

void Wall::draw(const Image::Sprite& image) const
{
    if (!burn_event_)
    {
        image.copy(State::OBJECT_IMAGE_WALL, Parent::point());
        return;
    }

    image.copy(State::OBJECT_IMAGE_BURNING_WALL, Parent::point());
}

bool Wall::is_burning() const { return !!burn_event_; }

void Wall::pause(unsigned now)
{
    if (burn_event_)
    {
        burn_event_->pause(now);
    }
}

void Wall::resume(unsigned now)
{
    if (burn_event_)
    {
        burn_event_->resume(now);
    }
}

void Wall::tick(unsigned now)
{
    if (burn_event_)
    {
        burn_event_->tick(now);

        if (burn_event_->did_complete())
        {
            Parent::did_die(true);
        }
    }
}

void Wall::will_burn(unsigned now, unsigned ms_to_completion)
{
    burn_event_ = new Event::Burn(now, ms_to_completion);
}

} // namespace Object

} // namespace Game
