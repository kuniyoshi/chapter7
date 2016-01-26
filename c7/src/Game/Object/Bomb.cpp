#include "Game/Object/Bomb.h"
#include <cmath>
#include <utility>
#include <vector>
#include "GameLib/Framework.h"
#include "Constants.h"
#include "Game/Event/Explode.h"
#include "Game/Event/Move.h"
#include "Game/Map.h"
#include "Image/Sprite.h"
#include "Piece.h"
#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "State.h"

namespace Game
{

namespace Object
{

namespace
{

const unsigned MsToStart = 3000;

} // namespace -

Bomb::Bomb(const Point& destination, int power, int owner_id, unsigned now)
:   Parent(destination),
    explode_event_(0),
    central_(),
    horizontal_(),
    vertical_(),
    will_explode_(false),
    owner_id_(owner_id)
{
    explode_event_ = new Event::Explode(now, power, MsToStart);
}

Bomb::~Bomb()
{
    SAFE_DELETE(explode_event_);
}

void Bomb::setup(   const Rect< double >& central,
                    const Rect< double >& horizontal,
                    const Rect< double >& vertical)
{
    central_ = central;
    horizontal_ = horizontal;
    vertical_ = vertical;
}

Rect< double > Bomb::central() const
{
    return central_;
}

void Bomb::will_explode()
{
    will_explode_ = true;
}

bool Bomb::did_complete_explosion() const { return Parent::did_die(); }

namespace
{

template< class T >
T mymin(T a, T b) { return b < a ? b : a; }

template< class T >
T mymax(T a, T b) { return b > a ? b : a; }

typedef std::pair< double, double > ddp;

bool does_segment_overlap(ddp a, ddp b)
{
    double min_a = mymin(a.first, a.second);
    a.first = a.first - min_a;
    a.second = a.second - min_a;
    b.first = b.first - min_a;
    b.second = b.second - min_a;

    if (mymax(b.first, b.second) < 0.0)
    {
        return false;
    }

    return mymin(b.first, b.second) <= mymax(a.first, a.second);
}

bool does_rect_overlap(const Rect< double >& a, const Rect< double >&b )
{
    if (!does_segment_overlap(ddp(a.left(), a.right()), ddp(b.left(), b.right())))
    {
        return false;
    }

    return does_segment_overlap(    ddp(a.top(), a.bottom()),
                                    ddp(b.top(), b.bottom()));
}

} // namespace -

bool Bomb::does_overlap(const Rect< double >& rect) const
{
    ASSERT(is_exploding());
    Point point = Parent::point();

    Rect< double > central(0.0, 1.0, 0.0, 1.0);
    central.add(point.x(), point.y());

    if (does_rect_overlap(rect, central))
    {
        return true;
    }

    for (int i = 0; i < Constants::DirectionNameSize; ++i)
    {
        Constants::DirectionName id = static_cast< Constants::DirectionName >(i);
        Point direction = Constants::direction(id);
        double length = explode_event_->length(id);
        Rect< double > explosion_rect;

        if (direction.y() == 0)
        {
            explosion_rect.top(horizontal_.top());
            explosion_rect.bottom(horizontal_.bottom());
            explosion_rect.left(direction.x() > 0 ? 0 : -length);
            explosion_rect.right(direction.x() > 0 ? 1 + length : 0);
        }
        else
        {
            explosion_rect.left(vertical_.left());
            explosion_rect.right(vertical_.right());
            explosion_rect.top(direction.y() > 0 ? 0 : -length);
            explosion_rect.bottom(direction.y() > 0 ? 1 + length : 0);
        }

        explosion_rect.add(point.x(), point.y());

        if (does_rect_overlap(rect, explosion_rect))
        {
            return true;
        }
    }

    return false;
}

void Bomb::draw(const Image::Sprite& image) const
{
    ASSERT(explode_event_);

    GameLib::Framework f = GameLib::Framework::instance();
    Size size(f.width(), f.height());
    unsigned* vram = f.videoMemory();

    if (!explode_event_->is_exploding())
    {
        image.copy_alpha_blend( State::OBJECT_IMAGE_BOMB,
                                explode_event_->get_alpha(),
                                Parent::point(),
                                size,
                                vram);
        return;
    }

    for (int i = 0; i < Constants::DirectionNameSize; ++i)
    {
        Constants::DirectionName d_id
        = static_cast< Constants::DirectionName >(i);
        Point direction = Constants::direction(d_id);
        double length = explode_event_->length(d_id);
        Point point = Parent::point();
        State::ObjectImage id = direction.x() == 0
        ? State::OBJECT_IMAGE_VERTICAL_STORM
        : State::OBJECT_IMAGE_HORIZONTAL_STORM;

        for (int power = 0; power < static_cast< int >(length); ++power)
        {
            point = point + direction;
            image.copy_alpha_blend( id,
                                    explode_event_->get_alpha(),
                                    point,
                                    size,
                                    vram);
        }

        double remained_length = length - static_cast< int >(length);

        if (remained_length == 0.0)
        {
            continue;
        }

        Event::Move move_event(0, 1000, point, direction);
        move_event.tick(static_cast< unsigned >(1000 * remained_length));

        image.copy_alpha_blend( id,
                                explode_event_->get_alpha(),
                                move_event,
                                size,
                                vram);
    }

    image.copy( State::OBJECT_IMAGE_FLOOR,
                Parent::point(),
                size,
                vram);

    image.copy_alpha_blend( State::OBJECT_IMAGE_CROSS_STORM,
                            explode_event_->get_alpha(),
                            Parent::point(),
                            size,
                            vram);
}

bool Bomb::is_exploding() const
{
    ASSERT(explode_event_);
    return explode_event_->is_exploding();
}

bool Bomb::is_owner_same_as(int id) const { return id == owner_id_; }

Point Bomb::max_point(Constants::DirectionName id) const
{
    const Point direction = Constants::direction(id);
    const std::pair< bool, double > explosion_length
    = explode_event_->stopped_length(id);
    const bool did_stop = explosion_length.first;
    const int length = static_cast< int >(std::ceil(explosion_length.second));

    int reached_length = length;

    if (did_stop && length < explode_event_->power())
    {
        reached_length = reached_length + 1;
    }

    return Point (  Parent::point(),
                    reached_length * direction.x(),
                    reached_length * direction.y());
}

void Bomb::pause(unsigned now)
{
    explode_event_->pause(now);
}

void Bomb::resume(unsigned now)
{
    explode_event_->resume(now);
}

void Bomb::tick(unsigned now)
{
    HALT("Do not do this.");
}

void Bomb::tick(unsigned now, const Map& map)
{
    explode_event_->tick(now, Parent::point(), map);

    if (will_explode_ && !explode_event_->is_exploding())
    {
        explode_event_->explode();
    }

    if (explode_event_->did_complete())
    {
        Parent::did_die(true);
    }
}

} // namespace Object

} // namespace Game
