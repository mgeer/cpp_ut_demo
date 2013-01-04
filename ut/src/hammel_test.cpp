#include "using_bytes.h"
#include "memory_reader.h"
#include "hammal.h"
using namespace UTSample;

class HammalTest : public UsingBytes {
public:
	HammalTest() : pool(2, 1024) {}
protected:
	void start_hammal(std::string content, size_t reading_unit_in_byte, 
		size_t segment_offset, size_t segment_size, BlockQueue& queue) {
		MemoryReader reader(content);
		Segment segment;
		segment.offset = segment_offset;
		segment.size = segment_size;
		Hammal hammal(segment, reader, queue, reading_unit_in_byte, pool);
		hammal.start();
	}

	BufferPool pool;
};

TEST_F(HammalTest, it_saves_blocks_into_block_queue) {
	size_t reading_unit_in_byte = 5;
	BlockQueue queue(2);
	start_hammal("12345abcde\nABCDE", reading_unit_in_byte, 0, 10, queue);
	Block block = queue.dequeue();
	ASSERT_TEXT("12345", block.buffer, block.size);
	block = queue.dequeue();
	ASSERT_TEXT("abcde", block.buffer, block.size);
}

TEST_F(HammalTest, it_creates_block_with_id) {
	size_t reading_unit_in_byte = 5;
	BlockQueue queue(2);
	start_hammal("12345abcde\nABCDE", reading_unit_in_byte, 0, 10, queue);
	Block block = queue.dequeue();
	ASSERT_EQ(0, block.id);
	block = queue.dequeue();
	ASSERT_EQ(1, block.id);
}

TEST_F(HammalTest, it_calculates_id_by_offset_and_reading_unit) {
	size_t reading_unit_in_byte = 5;
	BlockQueue queue(1);
	start_hammal("12345abcde\nABCDE", reading_unit_in_byte, 10, 5, queue);
	Block block = queue.dequeue();
	ASSERT_EQ(2, block.id);
}


TEST_F(HammalTest, it_reads_content_less_than_reading_unit) {
	size_t reading_unit_in_byte = 5;
	BlockQueue queue(2);
	start_hammal("12345abc", reading_unit_in_byte, 5, 3, queue);
	Block block = queue.dequeue();
	ASSERT_TEXT("abc", block.buffer, block.size);
}

