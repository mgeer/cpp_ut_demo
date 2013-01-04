#ifndef __UT_SAMPLE_RESULT_MERGER_H__
#define __UT_SAMPLE_RESULT_MERGER_H__
#include "mapper.h"
namespace UTSample {
class ResultMerger {
public:
    void merge(Result& source, Result& another, Mapper& mapper);

    inline bool is_one_line(std::vector<char>& line) {
        return line.size() != 0 && line[line.size() - 1] == '\n';
    }

    inline void concatenate(std::vector<char>& first, std::vector<char>& second) {
        first.insert(first.end(), second.begin(), second.end());
    }
};
}
#endif
