#include "using_result.h"
#include "result_collector.h"
#include "char_counter_mapper.h"
using namespace UTSample;

class ResultCollectorTest : public UsingResult {
protected:
	CharCounterMapper mapper;
};

TEST_F(ResultCollectorTest, it_is_integrited_when_result_count_equals_block_count) {
	ResultCollector collector(3);
	collector.create_result(0);
	collector.create_result(1);
	collector.create_result(2);
    ASSERT_TRUE(collector.check_integrity());
}

TEST_F(ResultCollectorTest, it_collects_results) {
	ResultCollector collector(3);
	create_result(collector.create_result(0), "12\n", "45\n", 0);
    create_result(collector.create_result(1), "7\n", "bc\n", 1);
    create_result(collector.create_result(2), "\n", "BC\n", 2);
	Output output = collector.collect(mapper);
	ASSERT_EQ(12, output.total_word_count);
}

TEST_F(ResultCollectorTest, it_collects_empty_result) {
	ResultCollector collector(1);
    Output output;
	output= collector.collect(mapper);
	ASSERT_EQ(0, output.total_word_count);
}

TEST_F(ResultCollectorTest, it_collects_results_added_randomly) {
	ResultCollector collector(2);
	create_result(collector.create_result(0), "12\n", "45", 0);
    create_result(collector.create_result(1), "78", "", 0);
    Output output;
	output= collector.collect(mapper);
	ASSERT_EQ(2, output.total_word_count);
}
