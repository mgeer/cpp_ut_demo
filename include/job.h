#ifndef __UT_SAMPLE_JOB_JOB_H__
#define __UT_SAMPLE_JOB_JOB_H__
#include "def.h"
#include <vector>
namespace UTSample {
struct Segment {
    uint_64 offset;
    uint_64 size;
};

class Job {
public:
    Job(uint_64 job_size, uint_64 reading_unit_in_byte)
        : job_size(job_size), reading_unit_in_byte(reading_unit_in_byte) {}

    void seperate(size_t parallel, std::vector<Segment>& segments);
    uint_64 get_block_count();

private:
    uint_64 job_size;
    uint_64 reading_unit_in_byte;
};
}
#endif

