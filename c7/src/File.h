#ifndef BAKUDAN_FILE_H_
#define BAKUDAN_FILE_H_

class File
{
private:
	char* data_;
	int size_;

public:
	File(const char* filename);
	~File();
	char operator[](int i) const;

	const char* data() const;
	int size() const;
	unsigned get_unsigned(int position) const;
};

#endif
