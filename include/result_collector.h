#ifndef __UT_SAMPLE_RESULT_COLLECTOR_H__
#define __UT_SAMPLE_RESULT_COLLECTOR_H__
#include "mapper.h"
#include "lock.h"
namespace UTSample {
class ResultCollector {
public:
    ResultCollector(size_t total_count) 
        : total_count(total_count), mutex() {}

    Result* create_result(size_t id);
    bool check_integrity();
    Output collect(Mapper& mapper);
private:
    size_t total_count;
    std::map<size_t, Result*> results;
    MutexLock mutex;
};
}
#endif

