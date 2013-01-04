#include "using_result.h"
#include "char_counter_mapper.h"
#include "result_merger.h"
#include "result_collector.h"
using namespace UTSample;

class ResultMergerTest : public UsingResult {
protected:
	CharCounterMapper mapper;
	ResultMerger merger;
};

TEST_F(ResultMergerTest, it_keeps_first_head_as_new_head) {
	ResultCollector collector(2);
	Result* first = collector.create_result(0);
	Result* second = collector.create_result(1);
	create_result(first, "123\n", "23\n", 1);
	create_result(second, "c\n", "bc\n", 2);
	
	merger.merge(*first, *second, mapper);
	ASSERT_TEXT("123\n", first->head);
}

TEST_F(ResultMergerTest, it_keeps_tail_of_last_result) {
	ResultCollector collector(2);
	Result* first = collector.create_result(0);
	Result* second = collector.create_result(1);

	create_result(first, "123\n", "ab", 0);
    create_result(second, "c\n", "DE", 1);
	merger.merge(*first, *second, mapper);
	ASSERT_TEXT("DE", first->tail);
}

TEST_F(ResultMergerTest, it_merges_output) {
	ResultCollector collector(2);
	Result* first = collector.create_result(0);
	Result* second = collector.create_result(1);

	create_result(first, "123\n", "ab", 2);
    create_result(second, "c\n", "DE", 2);
    merger.merge(*first, *second, mapper);
	ASSERT_EQ(7, first->output.total_word_count);
}

TEST_F(ResultMergerTest, it_handles_only_one_line_is_found) {
	ResultCollector collector(2);
	Result* first = collector.create_result(0);
	Result* second = collector.create_result(1);

	create_result(first, "123\n","ab", 0);
	create_result(second, "c\n", "DE", 0);
	merger.merge(*first, *second, mapper);
	ASSERT_EQ(3, first->output.total_word_count);
}

TEST_F(ResultMergerTest, it_shift_head_to_nextresult_if_output_and_tail_are_empty) {
	ResultCollector collector(2);
	Result* first = collector.create_result(0);
	Result* second = collector.create_result(1);

	create_result(first, "1", "", 0);
    create_result(second, "2", "", 0);
    merger.merge(*first, *second, mapper);
    ASSERT_TEXT("12", first->head);
}

TEST_F(ResultMergerTest, it_merges_next_head_to_first_head_which_is_not_a_line) {
	ResultCollector collector(2);
	Result* first = collector.create_result(0);
	Result* second = collector.create_result(1);

	create_result(first, "12", "", 0);
	create_result(second, "\n", "ab", 0);
	merger.merge(*first, *second, mapper);
	ASSERT_TEXT("12\n", first->head);
	ASSERT_TEXT("ab", first->tail);
}

TEST_F(ResultMergerTest, it_maps_miss_line_when_return_is_found) {
	ResultCollector collector(2);
	Result* first = collector.create_result(0);
	Result* second = collector.create_result(1);

	create_result(first, "12\n","ba", 0);
    create_result(second, "\n", "", 0);
    merger.merge(*first, *second, mapper);
    ASSERT_TEXT("12\n", first->head);
	ASSERT_EQ(2, first->output.total_word_count);
	ASSERT_TEXT("", first->tail);
}

