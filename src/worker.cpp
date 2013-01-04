#include <iostream>
#include "worker.h"
namespace UTSample {

void Worker::start() {
    Task task;
    while (true) {
        Block block = queue.dequeue(); 
        if (block.empty()) {
            break;
        }
        Result* result = collector.create_result(block.id);
        task.map(block, mapper, *result);
        pool.return_buffer(block.buffer);
        //std::cout << "---" << block.id << "finished" << std::endl;
    }
}

}

