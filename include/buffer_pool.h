#ifndef __UT_SAMPLE_BUFFER_POOL_H__
#define __UT_SAMPLE_BUFFER_POOL_H__
#include <queue>
#include "lock.h"

namespace UTSample {
class BufferPool {
public:
    BufferPool(size_t buffer_count, size_t buffer_size) : 
    buffer_count(buffer_count), 
    buffer_size(buffer_size),
    created_count(0),
    mutex(),
    not_empty(mutex) {
        while (created_count < buffer_count) {
            char* buffer = new char[buffer_size];
            queue.push(buffer);
            created_count++;
        }
    }
    virtual ~BufferPool() {
        while (!queue.empty()) {
            char* buffer = queue.front();
            queue.pop();
            delete[] buffer;
        }
    }
    char* get_buffer();
    void return_buffer(const char* buffer);
private:
    std::queue<char*> queue;
    size_t buffer_count;
    size_t buffer_size;
    size_t created_count;

    MutexLock mutex;
    Condition not_empty;
};
}
#endif

