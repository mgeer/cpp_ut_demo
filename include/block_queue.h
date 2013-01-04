#ifndef __UT_SAMPLE_BLOCK_QUEUE_H__
#define __UT_SAMPLE_BLOCK_QUEUE_H__
#include <queue>
#include "block.h"
#include "lock.h"

namespace UTSample {
class BlockQueue {
public:
    BlockQueue(size_t todo_count) : 
        todo_count(todo_count), 
        done_count(0),
        mutex(),
        not_empty(mutex) {}
    virtual ~BlockQueue() {};

    Block dequeue();
    void enqueue(const Block& block);

private:
    size_t todo_count;
    size_t done_count;
    std::queue<Block> queue;
    MutexLock mutex;
    Condition not_empty;

    bool finished() {
        return done_count >= todo_count;
    }
};
}
#endif

