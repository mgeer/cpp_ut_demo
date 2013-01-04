#include "using_result.h"
#include "char_counter_mapper.h"
#include "worker.h"
using namespace UTSample;

class WorkerTest : public UsingResult {
public:
	WorkerTest() : pool(5, 100) {}
protected:
	CharCounterMapper mapper;
	BufferPool pool;
	Block get_block(size_t id, std::string content) {
		char* buffer = pool.get_buffer();
		strncpy(buffer, content.c_str(), content.size());
		return Block(id, buffer, content.size());
	}
};

TEST_F(WorkerTest, it_works_when_block_queue_is_empty) {
	ResultCollector collector(0);
	BlockQueue queue(0);
	Worker worker(queue, collector, mapper, pool);
	worker.start();
	ASSERT_TRUE(queue.dequeue().empty());
}

TEST_F(WorkerTest, it_gets_work_from_queue_then_puts_result_into_collector) {
	ResultCollector collector(2);
	BlockQueue queue(2);
	Block block0 = get_block(0, std::string("1").c_str());
	Block block1 = get_block(1, std::string("a").c_str());
	queue.enqueue(block0);
	queue.enqueue(block1);
	Worker worker(queue, collector, mapper, pool);
	worker.start();
	ASSERT_TRUE(queue.dequeue().empty());
	ASSERT_TRUE(collector.check_integrity());
}

TEST_F(WorkerTest, it_maps_blocks) {
	ResultCollector collector(2);
	BlockQueue queue(2);
	Block block0 = get_block(0, std::string("abc\n").c_str());
	Block block1 = get_block(1, std::string("123\n").c_str());
	queue.enqueue(block0);
	queue.enqueue(block1);
	Worker worker(queue, collector, mapper, pool);
	worker.start();
	Output output = collector.collect(mapper);
	ASSERT_EQ(6, output.total_word_count);
}

TEST_F(WorkerTest, it_thinks_queue_is_finished_when_empty_block_is_received) {
	ResultCollector collector(2);
	BlockQueue queue(2);
	Block empty_block = get_block(0, std::string("").c_str());
	Block block0 = get_block(0, std::string("123\n").c_str());
	queue.enqueue(empty_block);
	queue.enqueue(block0);
	Worker worker(queue, collector, mapper, pool);
	worker.start();
	Output output = collector.collect(mapper);
	ASSERT_EQ(0, output.total_word_count);
}


