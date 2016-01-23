#ifndef BAKUDAN_RECT_H_
#define BAKUDAN_RECT_H_

template< class T >
class Rect
{
private:
    T left_;
    T right_;
    T top_;
    T bottom_;
public:
    Rect();
    Rect(T left, T right, T top, T bottom);
    Rect(const Rect< T >& base);
    T left() const;
    void left(T new_value);
    T right() const;
    void right(T new_value);
    T top() const;
    void top(T new_value);
    T bottom() const;
    void bottom(T new_value);
};

#endif
