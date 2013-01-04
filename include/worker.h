#ifndef __UT_SAMPLE_WORKER_H__
#define __UT_SAMPLE_WORKER_H__
#include "result_collector.h"
#include "block_queue.h"
#include "task.h"
#include "buffer_pool.h"

namespace UTSample {
class Worker {
public:
    Worker(BlockQueue& queue, ResultCollector& collector, 
            Mapper& mapper, BufferPool& pool) : 
                queue(queue), collector(collector), mapper(mapper), pool(pool) {}
    void start();

private:
    BlockQueue& queue;
    ResultCollector& collector;
    Mapper& mapper;
    BufferPool& pool;
};
}
#endif

