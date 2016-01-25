#ifndef BAKUDAN_CONSTANTS_H_
#define BAKUDAN_CONSTANTS_H_

class Point;

class Constants
{
public:
    enum PlayMode
    {
        PlayMode1P,
        PlayMode2P,
    };

    enum DirectionName
    {
        DirectionNameLeft,
        DirectionNameRight,
        DirectionNameTop,
        DirectionNameBottom,

        DirectionNameSize,
    };

public:
    static const Point& direction(DirectionName id);

public:
    Constants();
    ~Constants();
};

#endif
