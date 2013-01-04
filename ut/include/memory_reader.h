#include "reader.h"

class MemoryReader : public UTSample::Reader {
public:
	MemoryReader(std::string content) : content(content) {}

	size_t read(char* buffer, size_t offset, size_t count) {
		size_t read_count = 0;
		for (read_count; read_count < count && 
                read_count + offset < content.size(); read_count++) {
			buffer[read_count] = content[read_count + offset];
		}
		return read_count;
	}

	uint_64 get_total_size() {
		return content.size();
	}
private:
	std::string content;
};

