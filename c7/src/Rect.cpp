#include "Rect.h"

template< class T >
Rect< T >::Rect()
: left_(0), right_(0), top_(0), bottom_(0)
{}

template< class T >
Rect< T >::Rect(T left, T right, T top, T bottom)
: left_(left), right_(right), top_(top), bottom_(bottom)
{}

template< class T >
Rect< T >::Rect(const Rect< T >& base)
: left_(base.left_), right_(base.right_), top_(base.top_), bottom_(base.bottom_)
{}

template< class T >
T Rect< T >::left() const { return left_; }
template< class T >
void Rect< T >::left(T new_value) { left_ = new_value; }

template< class T >
T Rect< T >::right() const { return right_; }
template< class T >
void Rect< T >::right(T new_value) { right_ = new_value; }

template< class T >
T Rect< T >::top() const { return top_; }
template< class T >
void Rect< T >::top(T new_value) { top_ = new_value; }

template< class T >
T Rect< T >::bottom() const { return bottom_; }
template< class T >
void Rect< T >::bottom(T new_value) { bottom_ = new_value; }

template< class T >
void Rect< T >::add(T x, T y)
{
    left_ = left_ + x;
    right_ = right_ + x;
    top_ = top_ + y;
    bottom_ = bottom_ + y;
}

template Rect< double >::Rect();
template Rect< double >::Rect(double, double, double, double);
template Rect< double >::Rect(const Rect< double >&);
template double Rect< double >::left() const;
template void Rect< double >::left(double);
template double Rect< double >::right() const;
template void Rect< double >::right(double);
template double Rect< double >::top() const;
template void Rect< double >::top(double);
template double Rect< double >::bottom() const;
template void Rect< double >::bottom(double);
template void Rect< double >::add(double, double);
