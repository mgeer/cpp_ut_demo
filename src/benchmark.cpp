#include <iostream>
#include "benchmark.h"
namespace UTSample {

void Benchmark::start() {
    start_time_in_second = time(NULL);
}

int Benchmark::end() {
    if ( start_time_in_second == 0 ) {
        return -1;
    }
    time_t end_time_in_second = time(NULL);
    int lasted_time = end_time_in_second - start_time_in_second;
    start_time_in_second = 0;
    return lasted_time;
}

}

