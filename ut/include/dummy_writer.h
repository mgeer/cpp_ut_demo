#include "writer.h"

class DummyWriter : public fcexercise::Writer {
public:
	DummyWriter(const char* file) : file(file) {}
public:
	size_t write(const fcexercise::Output& output) {
		FILE *file_ptr = fopen(file, "w");
		if (NULL == file_ptr)
			return 0;
	
		char buffer[4];
		itoa(output.total_word_count, buffer, 10);
		size_t written_size = fwrite(buffer, 4, 1, file_ptr);
		fclose(file_ptr);
		return written_size;
	}

private:
	const char* file;
};

