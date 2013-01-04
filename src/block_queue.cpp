#include "block_queue.h"
namespace UTSample {

Block BlockQueue::dequeue() {
    Block block;
    {
        MutexLockGuard lock(mutex);
        if (finished()) {
            return block;
        }
        while (queue.empty()) {
            not_empty.wait();	
            if (finished()) {
                return block;
            }
        }
        block = queue.front();
        queue.pop();
        done_count++;
    }
    return block;
};

void BlockQueue::enqueue(const Block& block) {
    {
        MutexLockGuard lock(mutex);
        queue.push(block);
    }
    not_empty.notifyAll();
}

}

