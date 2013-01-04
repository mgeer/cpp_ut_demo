#include "simple_word_mapper.h"
#include <sstream>
#include "term.h"

namespace UTSample {

void SimpleWordMapper::map( const char* input, size_t offset, size_t count, 
                        std::vector<Term>& terms, std::vector<Term>& basic_words) {
    size_t word_index = 8;
    size_t tab_index = 0;
    size_t pointer = offset;

    for (; tab_index < word_index && pointer < count + offset; pointer++) {
        if ( *(input + pointer) == '\t') {
            tab_index++;
        }
    }
    if (tab_index < word_index) {
        return;
    }

    size_t word_end = pointer;
    for (word_end; word_end < count + offset; word_end++) {
        if (*(input + word_end) == '\t') {
            break;
        }
    }
    if (word_end == count + offset) {
        return;
    }

    Term term(input + pointer, word_end - pointer);
    size_t cut_count = cutter.cut(term, terms);
    if (cut_count == 1) {
        basic_words.push_back(*(terms.end() - 1));
    }
}

void SimpleWordMapper::map(Output& first, Output& another) {
    first.total_word_count += another.total_word_count;
    std::map<Term, size_t>::const_iterator iter;
    for (iter = another.terms.begin(); iter != another.terms.end(); iter++) {
        update_map((*iter).first, (*iter).second, first.terms, first);
    }
    for (iter = another.basic_words.begin(); iter != another.basic_words.end(); iter++) {
        update_map((*iter).first, (*iter).second, first.basic_words, first);
    }
}

void SimpleWordMapper::map( std::vector<Term>& terms, std::vector<Term>& basic_words, Output& output) {
    output.total_word_count += terms.size();
    map(terms, output.terms, output);
    map(basic_words, output.basic_words, output);
}

void SimpleWordMapper::map(std::vector<Term>& terms, std::map<Term, 
                                        size_t>& target, Output& output) {
    if (terms.size() == 0) {
        return;
    }
    std::sort(terms.begin(), terms.end());
    Term term = terms[0];
    size_t count = 1;
    for (size_t i = 1, i_end = terms.size(); i < i_end; i++) {
        if (terms[i] == term) {
            count++;
        }
        else {
            update_map(term, count, target, output);
            term = terms[i];
            count = 1;
        }
    }
    update_map(term, count, target, output);
}

void SimpleWordMapper::update_map(const Term& term, size_t count, 
                                    std::map<Term, size_t>& map, Output& output) {
    std::map<Term, size_t>::iterator iter = map.find(term);
    if (iter == map.end()) {
        map[output.copy_term(term)] = count;
    }
    else {
        map[term] += count;
    }
}

}

