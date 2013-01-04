#ifndef __UT_SAMPLE_SIMPLE_WORD_MAPPER_H__
#define __UT_SAMPLE_SIMPLE_WORD_MAPPER_H__
#include "mapper.h"
#include <algorithm>
#include "word_cutter.h"
namespace UTSample {
class SimpleWordMapper : public Mapper {
public:
    void map(const char* input, size_t offset, size_t count, 
            std::vector<Term>& terms, std::vector<Term>& basic_words);
    void map(std::vector<Term>& terms, std::vector<Term>& basic_words, 
            Output& output);
    void map(Output& first, Output& another);
    
private:
    WordCutter cutter;
    void SimpleWordMapper::update_map(const Term& term, size_t count, 
            std::map<Term, size_t>& map, Output& output);

    void map(std::vector<Term>& terms, std::map<Term, 
            size_t>& target, Output& output);
};
}
#endif

