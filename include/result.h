#ifndef __UT_SAMPLE_RESULT_H__
#define __UT_SAMPLE_RESULT_H__
#include <vector>
#include "output.h"
namespace UTSample {
class Result {
public:
    Result() : id(0), head(), tail(), output() {}
    Result(size_t id) : id(id), head(), tail(), output() {}
    std::vector<char> head;
    std::vector<char> tail;
    Output output;
    size_t id;
};
}
#endif

