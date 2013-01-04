#include "using_bytes.h"
#include "job.h"

using namespace UTSample;

class JobTest : public UsingBytes {
protected:
	static const size_t READING_UNIT_10 = 10;
    static const size_t JOB_LENGTH_100 = 100;
	
	void seperate(size_t job_size, int parallel, 
            size_t readingUnit, std::vector<struct Segment>& segments) {
        Job job(job_size, readingUnit);
        job.seperate(parallel, segments);
    }
};

TEST_F(JobTest, it_seperates_job_by_parallel) {
	std::vector<struct Segment> segments;
	seperate(JOB_LENGTH_100, 3, READING_UNIT_10, segments);
	ASSERT_EQ(3, segments.size());
}

TEST_F(JobTest, it_has_max_parallel) {
	std::vector<struct Segment> segments;
	seperate(JOB_LENGTH_100, 12, READING_UNIT_10, segments);
    ASSERT_EQ(10, segments.size());

	segments.clear();
    seperate(JOB_LENGTH_100 + 5, 12, READING_UNIT_10, segments);
    ASSERT_EQ(11, segments.size());
}

TEST_F(JobTest, it_assigns_offset_to_segment) {
	std::vector<struct Segment> segments;
	seperate(JOB_LENGTH_100, 3, READING_UNIT_10, segments);
	ASSERT_EQ(0, segments[0].offset);
    ASSERT_EQ(40, segments[1].offset);
    ASSERT_EQ(70, segments[2].offset);
}

TEST_F(JobTest, it_assigns_size_to_segment) {
	std::vector<struct Segment> segments;
	seperate(JOB_LENGTH_100, 3, READING_UNIT_10, segments);
    ASSERT_EQ(40, segments[0].size);
    ASSERT_EQ(30, segments[1].size);
    ASSERT_EQ(30, segments[2].size);
}

TEST_F(JobTest, it_assignes_job_reminder_to_last_segment) {
	std::vector<struct Segment> segments;
	seperate(JOB_LENGTH_100 + 5, 3, READING_UNIT_10, segments);
    ASSERT_EQ(40, segments[0].size);
    ASSERT_EQ(30, segments[1].size);
    ASSERT_EQ(35, segments[2].size);
}

TEST_F(JobTest, it_handles_job_length_less_than_reading_unit) {
	std::vector<struct Segment> segments;
	seperate(10, 2, 100, segments);
    ASSERT_EQ(1, segments.size());
    ASSERT_EQ(10, segments[0].size);
}

TEST_F(JobTest, it_get_blocks_count) {
    Job job(105, 10);
    ASSERT_EQ(11, job.get_block_count());
}

void ASSERT_SEGMENT(uint_64 size, uint_64 offset, Segment& segment) {
	ASSERT_EQ(size, segment.size);
	ASSERT_EQ(offset, segment.offset);
}

TEST_F(JobTest, it_supports_large_file) {
	uint_64 g_bytes = 1024 * 1024 * 1024;
	Job job(30 * g_bytes, 1024 * 1024);
	std::vector<Segment> segments;
	job.seperate(3, segments);
	ASSERT_SEGMENT(10 * g_bytes, 0, segments[0]);
	ASSERT_SEGMENT(10 * g_bytes, 10 * g_bytes, segments[1]);
	ASSERT_SEGMENT(10 * g_bytes, 20 * g_bytes, segments[2]);
}
