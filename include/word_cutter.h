#ifndef __UT_SAMPLE_CUTTER_H__
#define __UT_SAMPLE_CUTTER_H__
#include <vector>
#include "term.h"
namespace UTSample {
class WordCutter {
public:
    size_t cut(Term word, std::vector<Term>& terms) {
        size_t pointer = 0;
        for (; pointer < word.size && *(word.content + pointer) == ' '; pointer++);

        size_t end = word.size;
        for (; end > pointer && *(word.content + end - 1) == ' '; end--);

        if (end <= pointer) {
            return 0;
        }

        size_t word_count = 0;
        for (size_t i = pointer; i < end; i++) {
            if (*(word.content + i) == ' ') {
                terms.push_back(Term(word.content, i - pointer));
                pointer = i + 1;
                word_count++;
            }
        }
        terms.push_back(Term(word.content + pointer, end - pointer));
        return word_count + 1;
    }
};
}
#endif

