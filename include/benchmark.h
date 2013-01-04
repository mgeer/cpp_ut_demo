#ifndef __UT_SAMPLE_BENCHMARK_H__
#define __UT_SAMPLE_BENCHMARK_H__
#include <stdio.h>
#include <time.h>

namespace UTSample {
class Benchmark {
public:
    void start();
    int end();
    Benchmark() : start_time_in_second(0) {}
private:
    time_t start_time_in_second;
};
}

#endif

