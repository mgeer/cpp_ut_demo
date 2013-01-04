#include "using_result.h"
#include "task.h"
#include "char_counter_mapper.h"
using namespace UTSample;

class TaskTest : public UsingResult {
protected:
	void run_task(std::string content, Result& result) {
		Block block(0, content.c_str(), content.size());
		task.map(block, mapper, result);
	}
	CharCounterMapper mapper;
	Task task;
};

TEST_F(TaskTest, it_copys_block_id_to_result_id) {
	Block block(2012, std::string("abc").c_str(), 3);
	Result result(2012);
	task.map(block, mapper, result);
	ASSERT_EQ(2012, result.id);
}

TEST_F(TaskTest, it_maps_integrated_segment) {
	Result result(0);
	run_task("\n12\nab\nAB\n", result);
	ASSERT_EQ(6, result.output.total_word_count);
}

TEST_F(TaskTest, it_saves_residue_head_and_tail) {
	Result result(0);
	run_task("678\nabc\nABCDEFG", result);
	ASSERT_EQ(3, result.output.total_word_count);
	ASSERT_TEXT("678\n", result.head);
	ASSERT_TEXT("ABCDEFG", result.tail);
}

TEST_F(TaskTest, it_records_tail_as_null_for_stream_end_with_return) {
	Result result(0);
	run_task("678\nabcdefgh\nABCDEFG\n", result);
	ASSERT_TEXT("", result.tail);
}

TEST_F(TaskTest, it_handles_one_line_without_return) {
	Result result(0);
	run_task("123", result);
    ASSERT_TEXT("123", result.head);
}

TEST_F(TaskTest, it_handles_one_line_with_return) {
	Result result(0);
	run_task("123\n", result);
    ASSERT_TEXT("123\n", result.head);
}

TEST_F(TaskTest, it_maps_return) {
	Result result(0);
	run_task("\n", result);
	ASSERT_EQ(0, result.output.total_word_count);
}


