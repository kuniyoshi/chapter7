#pragma once

template< class T >
class Array2D {
private:
	T* array_;
	int size0_;
	int size1_;

public:
	Array2D();
	~Array2D();
	void set_size(int size0, int size1);
	T& operator()(int index0, int index1);
	const T& operator()(int index0, int index1) const;
};
