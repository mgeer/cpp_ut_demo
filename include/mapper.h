#ifndef __UT_SAMPLE_MAPPER_H__
#define __UT_SAMPLE_MAPPER_H__
#include <vector>
#include "result.h"
#include "term.h"

namespace UTSample {
class Mapper {
public:
    virtual void map(const char* input, size_t offset, size_t count, 
            std::vector<Term>& terms, std::vector<Term>& basic_words) = 0;

    virtual void map(Output& first, Output& another) = 0;

    virtual void map(std::vector<Term>& terms, std::vector<Term>& basic_words, 
            Output& output) = 0;
};
}
#endif

