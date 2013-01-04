#ifndef __UT_SAMPLE_OUTPUT_H__
#define __UT_SAMPLE_OUTPUT_H__
#include <map>
#include <vector>
#include "term.h"
namespace UTSample {
class Output {
    public:
    Output() : total_word_count(0), terms(), basic_words(), buffers() {}
    ~Output() {
        for(size_t i = 0, i_end = buffers.size(); i < i_end; i++) {
            delete[] buffers[i];
        }
    }
    
    size_t total_word_count;
    std::map<Term, size_t> terms;
    std::map<Term, size_t> basic_words;
    
    std::vector<char*> buffers;
    Term copy_term(Term term) {
        char* buffer = new char[term.size];
        memcpy(buffer, term.content, term.size);
        buffers.push_back(buffer);
        return Term(buffer, term.size);
    }
};
}
#endif


