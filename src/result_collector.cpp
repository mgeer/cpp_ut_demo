#include "result_collector.h"
#include "result_merger.h"
#include <iostream>
namespace UTSample {

Result* ResultCollector::create_result(size_t id) {
    MutexLockGuard lock(mutex);
    Result* result = new Result(id);
    results[id] = result;
    return result;
}

bool ResultCollector::check_integrity() {
    return results.size() == total_count;
}

Output ResultCollector::collect(Mapper& mapper) {
    Output output;
    if (results.size() == 0) {
        return output;
    }
    Result *result = results[0];
    ResultMerger merger;
    for (size_t i = 1, i_end = results.size(); i < i_end; i++) {
        merger.merge(*result, *(results[i]), mapper);
    }
    std::vector<Term> terms, basic_words;
    mapper.map(&result->head[0], 0, result->head.size(), terms, basic_words);
    mapper.map(terms, basic_words, result->output);
    return result->output;
}

}

