#ifndef __UT_SAMPLE_HAMMAL__
#define __UT_SAMPLE_HAMMAL__
#include "job.h"
#include "reader.h"
#include "block_queue.h"
#include "buffer_pool.h"

namespace UTSample {
class Hammal {
public:
    Hammal(Segment segment, Reader& reader, BlockQueue& block_queue, 
            size_t reading_unit_in_byte, BufferPool& pool)
        :segment(segment), 
        reader(reader), 
        block_queue(block_queue), 
        reading_unit_in_byte(reading_unit_in_byte),
        pool(pool) {}

    void start();

private:
    Segment segment;
    Reader& reader;
    BlockQueue& block_queue;
    size_t reading_unit_in_byte;
    BufferPool& pool;
};
}
#endif

