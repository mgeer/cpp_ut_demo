#ifndef __UT_SAMPLE_JOB_CONFIGURATION_H__
#define __UT_SAMPLE_JOB_CONFIGURATION_H__
#include <cstddef>

namespace UTSample {
struct JobConfiguration {
    JobConfiguration(
        size_t hammal_count, 
        size_t reading_unit_in_byte, 
        size_t worker_count, 
        size_t block_buffer_count) 
        : hammal_count(hammal_count),
        reading_unit_in_byte(reading_unit_in_byte),
        worker_count(worker_count),
        block_buffer_count(block_buffer_count)
     {}

    size_t hammal_count;
    size_t reading_unit_in_byte;
    size_t worker_count;
    size_t block_buffer_count;
};
}
#endif

