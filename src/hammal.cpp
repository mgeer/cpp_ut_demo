#include "hammal.h"

namespace UTSample {

void Hammal::start() {
    uint_64 offset = segment.offset;
    uint_64 readIndex = segment.offset / reading_unit_in_byte;
    while (offset < segment.offset + segment.size) {
        uint_64 remain_count = segment.offset + segment.size - offset;
        uint_64 bytes_to_read = remain_count > reading_unit_in_byte 
            ? reading_unit_in_byte 
            : remain_count;

        char* buffer = pool.get_buffer();
        size_t bytes = reader.read(buffer, offset, bytes_to_read);
        if (0 == bytes) {
            std::cout << "read file error" << std::endl;
        }	
        Block block(readIndex, buffer, bytes);
        block_queue.enqueue(block);
        offset += bytes;
        readIndex++;
    }
}

}

