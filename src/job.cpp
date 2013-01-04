#include "job.h"
#include <iostream>
namespace UTSample {

void Job::seperate(size_t parallel, std::vector<Segment>& segments) {
    size_t block_count = get_block_count();
    parallel = parallel > block_count ? block_count : parallel;
    size_t integrited_block_count = job_size / reading_unit_in_byte;
    size_t block_count_for_parallel = integrited_block_count / parallel;
    size_t integrited_block_reminder = integrited_block_count % parallel;
    size_t job_reminder = job_size % reading_unit_in_byte;
    for (size_t i = 0; i < parallel; i++) {
        int block_count_for_segment = block_count_for_parallel;
        if (integrited_block_reminder > 0) {
            block_count_for_segment += 1;
            integrited_block_reminder--;
        }
        uint_64 size = (uint_64)block_count_for_segment * (uint_64)reading_unit_in_byte;
        uint_64 offset = 0;
        if (i > 0) {
            offset = segments[i - 1].offset + segments[i - 1].size;
        }
        if (i == parallel - 1 && job_reminder > 0) {
            size += job_reminder;
        }
        Segment segment;
        segment.offset = offset;
        segment.size = size;
        segments.push_back(segment);
    }
}

uint_64 Job::get_block_count() {
    uint_64 job_reminder = job_size % reading_unit_in_byte;
    uint_64 block_count = job_size / reading_unit_in_byte;
    return job_reminder > 0 ? block_count + 1 : block_count;
}

}

