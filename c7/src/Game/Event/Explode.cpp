#include "Game/Event/Explode.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <utility>
#include <vector>
#include "GameLib/GameLib.h"
#include "Constants.h"
#include "Game/Map.h"
#include "Point.h"

namespace Game
{

namespace Event
{

namespace
{

enum MsStatus
{
    MsStatusIgniting,
    MsStatusExploding,
    MsStatusKeepExploding,
    MsStatusWeaking,
    MsStatusSize,
};

// status at ms
// igniting: [0, ms_to_start_explosion[
// exploding: [.., .. + MsExploding[
// keep_exploding: [.., MsKeeping[
// weaking: [.., .. + MsWeaking[

const unsigned MsKeeping    = 500;
const unsigned MsWeaking    = 200;

// NG: 7700 m/s
// Sonic: 340 m/s
// v(t) = NG - a * t^2
// v(1[s]) = Sonic
// a = NG - Sonic
// F(t)[m] = NG * t - 1 / 3 * a * t^3
// F(1[s]) = 1[unit]
// F(t)[unit] = F(t)[m] / F(1)[m]
// F(1)[m] = NG * t - 1 / 3 * a * t^3

double calc_distance(unsigned ms);
double calc_unit(unsigned ms);

const unsigned MsExploding  = 1000;
const int Ng                = 7700;
const int Sonic             = 340;
const int CoefA             = Ng - Sonic;
const double Denominator    = calc_distance(MsExploding);
const double Epsilon        = calc_unit(MsExploding)
                                - calc_unit(MsExploding - 30);

double calc_distance(unsigned ms)
{
    double t = static_cast< double >(ms) / 1000;
    double l = static_cast< double >(Ng) * t - 1.0 / 3 * CoefA * std::pow(t, 3);
    return l;
}

double calc_unit(unsigned ms)
{
    ASSERT(ms <= MsExploding);
    return calc_distance(ms) / Denominator;
}

} // namespace -

Explode::Explode(unsigned now, int power, unsigned ms_to_start_explosion)
:   Parent(now),
    power_(power),
    max_lengths_(std::vector< std::pair< bool, double > >()),
    ms_statuses_(std::vector< unsigned >()),
    duration_(0)
{
    max_lengths_.reserve(Constants::DirectionNameSize);

    for (int i = 0; i < Constants::DirectionNameSize; ++i)
    {
        max_lengths_.push_back(std::pair< bool, double >(false, 0.0));
    }

    ms_statuses_.reserve(MsStatusSize);

    for (int i = 0; i < MsStatusSize; ++i)
    {
        ms_statuses_.push_back(0);
    }

    ms_statuses_.at(MsStatusIgniting) = ms_to_start_explosion;
    ms_statuses_.at(MsStatusExploding) = MsExploding;
    ms_statuses_.at(MsStatusKeepExploding) = MsKeeping;
    ms_statuses_.at(MsStatusWeaking) = MsWeaking;

    std::vector< unsigned >::iterator iterator = ms_statuses_.begin();
    unsigned acc = 0;

    for (; iterator != ms_statuses_.end(); ++iterator)
    {
        (*iterator) = acc + (*iterator);
        acc = (*iterator);
    }
}

Explode::~Explode() {}

int Explode::power() const { return power_; }

namespace 
{

MsStatus compute_status(unsigned duration, std::vector< unsigned >ms_statuses)
{
    std::vector< unsigned >::iterator iterator
    = std::find_if( ms_statuses.begin(),
                    ms_statuses.end(),
                    std::bind2nd(std::greater< unsigned >(), duration));
    int distance = iterator - ms_statuses.begin();
    distance = distance >= static_cast< int >(ms_statuses.size())
    ? ms_statuses.end() - ms_statuses.begin()
    : distance;
    return static_cast< MsStatus >(distance);
}

bool is_status_igniting(unsigned duration, std::vector< unsigned > ms_statuses)
{
    return compute_status(duration, ms_statuses) == MsStatusIgniting;
}

bool is_status_exploding(unsigned duration, std::vector< unsigned > ms_statuses)
{
    return compute_status(duration, ms_statuses) == MsStatusExploding;
}

bool is_status_keep_exploding(  unsigned duration,
                                std::vector< unsigned > ms_statuses)
{
    return compute_status(duration, ms_statuses) == MsStatusKeepExploding;
}

bool is_status_weaking(unsigned duration, std::vector< unsigned > ms_statuses)
{
    return compute_status(duration, ms_statuses) == MsStatusWeaking;
}

} // namespace -

bool Explode::did_complete() const
{
    return duration_ >= ms_statuses_.at(MsStatusWeaking);
}

void Explode::explode()
{
    if (is_status_igniting(duration_, ms_statuses_))
    {
        duration_ = ms_statuses_.at(MsStatusIgniting);
    }
}

namespace
{

double calc_alpha_on_igniting(  unsigned duration,
                                std::vector< unsigned > ms_statuses)
{
    unsigned ms_to_start_explosion = ms_statuses.at(MsStatusIgniting);

    if (duration > ms_to_start_explosion)
    {
        return 1.0;
    }

    unsigned ms_to_transmitting
    = ms_to_start_explosion - ms_to_start_explosion / 2;

    if (duration < ms_to_transmitting)
    {
        return 0.0;
    }

    unsigned diff1 = duration - ms_to_transmitting;
    unsigned diff2 = ms_to_start_explosion - ms_to_transmitting;
    double rate = static_cast< double >(diff1) / diff2;
    return std::pow(rate, 2);
}

double calc_alpha(  unsigned now,
                    unsigned min,
                    unsigned max,
                    double from,
                    double to)
{
    if (now < min)
    {
        return from;
    }

    if (now >= max)
    {
        return to;
    }

    if (min > max)
    {
        return from;
    }

    unsigned denominator = max - min;
    unsigned numerator = now - min;
    double rate = static_cast< double >(numerator) / denominator;
    return from + (to - from) * rate;
}

} // namespac -

double Explode::get_alpha() const
{
    if (is_status_igniting(duration_, ms_statuses_))
    {
        return calc_alpha_on_igniting(duration_, ms_statuses_);
    }
    else if (is_status_exploding(duration_, ms_statuses_))
    {
        return calc_alpha(  duration_,
                            ms_statuses_.at(MsStatusIgniting),
                            ms_statuses_.at(MsStatusExploding),
                            0.2,
                            0.1);
    }
    else if (is_status_keep_exploding(duration_, ms_statuses_))
    {
        return 0.1;
    }
    else // weaking
    {
        unsigned numerator = duration_ > ms_statuses_.at(MsStatusWeaking)
        ? 0
        : ms_statuses_.at(MsStatusWeaking) - duration_;
        unsigned denominator = ms_statuses_.at(MsStatusWeaking)
                                - ms_statuses_.at(MsStatusKeepExploding);
        double rate = static_cast< double >(numerator) / denominator;
        double alpha = 1 - std::pow(rate, 2);
        return alpha;
    }
}

bool Explode::is_exploding() const
{
    return !is_status_igniting(duration_, ms_statuses_);
}

double Explode::length(Constants::DirectionName id) const
{
    return max_lengths_.at(id).second;
}

std::pair< bool, double >
Explode::stopped_length(Constants::DirectionName id) const
{
    return max_lengths_.at(id);
}

void Explode::tick(unsigned now)
{
    HALT("do not use this.")
}

namespace
{

unsigned calc_exploding_ms( unsigned duration,
                            std::vector< unsigned > ms_statuses)
{
    if (duration > ms_statuses.at(MsStatusExploding))
    {
        return MsExploding;
    }
    else if (duration > ms_statuses.at(MsStatusIgniting))
    {
        return duration - ms_statuses.at(MsStatusIgniting);
    }
    else
    {
        return 0;
    }
}

} // namespace -

void Explode::tick(unsigned now, const Point& point, const Map& map)
{
    unsigned diff = now - Parent::last_stamp();
    duration_ = duration_ + diff;
    Parent::last_stamp(now);

    unsigned ms_exploding = calc_exploding_ms(duration_, ms_statuses_);
    double normalized_length = calc_unit(ms_exploding);
    double length = power_ * normalized_length;

    for (int i = 0; i < Constants::DirectionNameSize; ++i)
    {
        if (max_lengths_.at(i).first)
        {
            continue;
        }

        Constants::DirectionName id = static_cast< Constants::DirectionName >(i);
        double current_length = max_lengths_.at(id).second;
        bool did_stop = false;
        Point direction = Constants::direction(id);

        while (current_length < length)
        {
            int overed_length = static_cast< int >(std::ceil(current_length));
            Point current_point(    point,
                                    overed_length * direction.x(),
                                    overed_length * direction.y());

            if (map.is_block(current_point) || map.is_wall(current_point))
            {
                did_stop = true;
                current_length = std::floor(current_length);
                break;
            }

            current_length = current_length + 0.5;
        }

        if (did_stop)
        {
            max_lengths_.at(i).first = true;
            max_lengths_.at(i).second = current_length;
        }
        else
        {
            max_lengths_.at(i).second = length;
        }
    }
}

} // namespace Event

} // namespace Game
