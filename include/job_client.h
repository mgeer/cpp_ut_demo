#ifndef __UT_SAMPLE_JOB_CLIENT_H__
#define __UT_SAMPLE_JOB_CLIENT_H__
#include "job_configuration.h"
#include "hammal_factory.h"
#include "output_writer.h"
#include "mapper.h"
#include "job.h"
#include "hammal.h"
#include "worker.h"

namespace UTSample {
class JobClient {
public:
    JobClient(JobConfiguration configuration, HammalFactory& factory, 
            OutputWriter& writer) :
            configuration(configuration),
            factory(factory),
            writer(writer),
            workers(),
            worker_thread_ids()
             {}

    virtual ~JobClient() {
        for(size_t i = 0; i < workers.size(); i++) {
            delete workers[i];
        }
    }
    int run_job(Mapper& mapper);


private:
    JobConfiguration configuration;
    HammalFactory& factory;
    OutputWriter& writer;
    std::vector<Worker*> workers;
    std::vector<pthread_t> worker_thread_ids;

private:
    void ensure_block_buffer_count() {
        configuration.block_buffer_count = 
            configuration.block_buffer_count < configuration.worker_count ? 
            configuration.worker_count : configuration.block_buffer_count;
    }
    void start_hammals(Job& job, BlockQueue& block_queue, BufferPool& pool);

    void start_workers(BlockQueue& block_queue, ResultCollector& collector, 
        Mapper& mapper, BufferPool& pool);
};
}
#endif

