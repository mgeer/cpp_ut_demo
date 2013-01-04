#include <gtest.h>
#include "benchmark.h"
#include <unistd.h>

using namespace UTSample;
class BenchmarkTest : public testing::Test {
public:
	void SetUp() {}
	void TearDown() {}
};

void suspend(int seconds) {
	sleep(seconds);
}

TEST_F(BenchmarkTest, it_measures_time_consuming) {
	Benchmark benchmark;
	benchmark.start();
	int time_to_sleep = 1;
	suspend(time_to_sleep);
	ASSERT_TRUE(time_to_sleep <= benchmark.end());
}

TEST_F(BenchmarkTest, it_returns_error_if_end_is_called_before_start) {
	Benchmark benchmark;
	ASSERT_EQ(-1, benchmark.end());
}

TEST_F(BenchmarkTest, it_returns_error_if_end_is_called_after_end) {
	Benchmark benchmark;
	benchmark.start();
	benchmark.end();
	ASSERT_EQ(-1, benchmark.end());
}

