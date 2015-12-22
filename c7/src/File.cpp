#include <fstream>
#include "File.h"

using namespace std;

File::File(const char* filename) : data_(0), size_(0)
{
	ifstream in(filename, ifstream::binary);

	if (in)
	{
		in.seekg(0, fstream::end);
		size_ = static_cast< int >(in.tellg());
		in.seekg(0, fstream::beg);
		char* buffer = new char[size_];
		in.read(buffer, size_);
		data_ = buffer;
	}
}

File::~File()
{
	delete[] data_;
	data_ = 0;
}

char File::operator[](int i) const
{
	return data_[i];
}

const char* File::data() const
{
	return data_;
}

int File::size() const
{
	return size_;
}

unsigned File::get_unsigned(int position) const
{
	const unsigned char* casted_data = reinterpret_cast< const unsigned char* >(&(data_[position]));
	unsigned value = casted_data[0];
	value += casted_data[1] << 8;
	value += casted_data[2] << 16;
	value += casted_data[3] << 24;
	return value;
}
