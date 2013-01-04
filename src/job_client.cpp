#include "job_client.h"
namespace UTSample {

static void* start_hammal(void* arg) {
    Hammal* hammal = (Hammal*)arg;
    hammal->start();
    return (void*)0;
}

static void* start_worker(void* arg) {
    Worker* worker = (Worker*)arg;
    worker->start();
    return (void*)0;
}

void JobClient::start_hammals(Job& job, BlockQueue& block_queue, BufferPool& pool) {
    std::vector<Segment> segments;
    job.seperate(configuration.hammal_count, segments);
    for (size_t i = 0; i < segments.size(); i++) {
        Hammal* hammal = factory.create(segments[i], block_queue, configuration.reading_unit_in_byte, pool);
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, start_hammal, hammal);
    }
 }

 void JobClient::start_workers(BlockQueue& block_queue, ResultCollector& collector, 
     Mapper& mapper, BufferPool& pool) {
     for (size_t i = 0; i < configuration.worker_count; i++ ) {
        Worker* worker = new Worker(block_queue, collector, mapper, pool);
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, start_worker, worker);
        worker_thread_ids.push_back(thread_id);
        workers.push_back(worker);
    }
 }

 int JobClient::run_job(Mapper& mapper) {
    ensure_block_buffer_count();
    uint_64 job_size = factory.job_size();
    if (0 == job_size) {
        return -1;
    }
    
    Job job(job_size, configuration.reading_unit_in_byte);
    size_t total_count = job.get_block_count();
    BlockQueue block_queue(total_count);
    BufferPool pool(configuration.block_buffer_count, configuration.reading_unit_in_byte);
    start_hammals(job, block_queue, pool);
    ResultCollector collector(total_count);
    start_workers(block_queue, collector, mapper, pool);
    
    for (size_t i = 0; i < worker_thread_ids.size(); i++) {
        pthread_join(worker_thread_ids[i], NULL);
    }

    if (!collector.check_integrity()) {
        std::cout << "integrity error" << std::endl;
    }
    Output output = collector.collect(mapper);
    writer.write(output);
}

}

