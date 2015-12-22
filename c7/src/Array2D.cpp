#include "Array2D.h"
#include "State.h"
#include "Map.h"

template< class T >
Array2D< T >::Array2D() : array_(0) {}

template< class T >
Array2D< T >::~Array2D()
{
	delete[] array_;
	array_ = 0;
}

template< class T >
void Array2D< T >::set_size(int size0, int size1)
{
	size0_ = size0;
	size1_ = size1;
	array_ = new T[size0_ * size1_];
}

template< class T >
T& Array2D< T >::operator()(int index0, int index1)
{
	return array_[index1 * size0_ + index0];
}

template< class T >
const T& Array2D< T >::operator()(int index0, int index1) const
{
	return array_[index1 * size0_ + index0];
}

template Array2D< Map >::Array2D();
template Array2D< Map >::~Array2D();
template void Array2D< Map >::set_size(int, int);
template Map& Array2D< Map >::operator()(int, int);
template const Map& Array2D< Map >::operator()(int, int) const;
