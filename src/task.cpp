#include "task.h"

namespace UTSample {

size_t Task::save_head(Block& block, Result& result) {
    size_t count;
    for (count = 0; count < block.size; count++) {
        if (block.buffer[count] == '\n') {
            count++;
            break;
        }
    }
    result.head.insert(result.head.end(), &block.buffer[0], &block.buffer[count]);
    return count;
}

void Task::save_tail(Block& block, size_t tail_start, Result& result) {
    if (tail_start == block.size) {
        return;
    }
    result.tail.insert(result.tail.end(), &block.buffer[tail_start], &block.buffer[block.size]);
}

void Task::map(Block& block, Mapper& mapper, Result& result) {
    size_t pointer = save_head(block, result);
    std::vector<Term> terms, basic_words;
    for (size_t i = pointer; i < block.size; i++) {
        if (block.buffer[i] != '\n') {
            continue;
        }
        mapper.map(block.buffer, pointer, i - pointer + 1, terms, basic_words);
        pointer = i + 1;
    }
    mapper.map(terms, basic_words, result.output);
    save_tail(block, pointer, result);
}

}

