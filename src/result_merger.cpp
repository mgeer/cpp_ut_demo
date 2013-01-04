#include "result_merger.h"
namespace UTSample {

void ResultMerger::merge(Result& source, Result& another, Mapper& mapper) {
    if (!is_one_line(source.head)) {
        concatenate(source.head, another.head);
        source.tail = another.tail;
        return;
    }

    concatenate(source.tail, another.head);

    if (is_one_line(source.tail)) {
        std::vector<Term> terms;
        std::vector<Term> basic_words;
        mapper.map(&source.tail[0], 0, source.tail.size(), terms, basic_words);
        mapper.map(terms, basic_words, source.output);
        source.tail = another.tail;
    }
    mapper.map(source.output, another.output);
}

}

