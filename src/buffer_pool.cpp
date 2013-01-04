#include "buffer_pool.h"
namespace UTSample {

char* BufferPool::get_buffer() {
    char* buffer;
    {
        MutexLockGuard lock(mutex);
        while (queue.empty()) {
            not_empty.wait();	
        }
        buffer = queue.front();
        queue.pop();
    }
    return buffer;
}
void BufferPool::return_buffer(const char* buffer) {
    {
        MutexLockGuard lock(mutex);
        queue.push(const_cast<char*>(buffer));
    }
    not_empty.notifyAll();
}

}

