#include "using_bytes.h"
#include "block_queue.h"

using namespace UTSample;
class BlockQueueTest : public UsingBytes {
protected:
	BlockQueueTest() : queue(2) {
	}
protected:
	BlockQueue queue;
};


TEST_F(BlockQueueTest, it_is_not_finished_when_not_all_blocks_are_handled) {
	Block block(0, std::string("").c_str(), 1);
    queue.enqueue(block);
    queue.enqueue(block);
	ASSERT_FALSE(queue.dequeue().empty());
	ASSERT_FALSE(queue.dequeue().empty());
}

TEST_F(BlockQueueTest, it_is_finished_when_all_blocks_are_handled) {
	Block block(0, std::string("").c_str(), 0);
    queue.enqueue(block);
    queue.enqueue(block);
	queue.dequeue();
	queue.dequeue();
	ASSERT_TRUE(queue.dequeue().empty());
}

