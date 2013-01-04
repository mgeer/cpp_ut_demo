#include "using_bytes.h"
#include "job_client.h"
#include "simple_word_mapper.h"
#include "output_writer.h"
#include "disk_hammal_factory.h"
#include "disk_reader.h"
#include "benchmark.h"
using namespace UTSample;

class PerformanceTest : public UsingBytes {
};

TEST_F(PerformanceTest, DISABLED_test_performance) {
	DiskHammalFactory factory(GBYTES11FILE);
	OutputWriter writer(GBYTESRESULT);
	JobConfiguration configuration(1, 150 * 1024 * 1024, 10, 20);
	JobClient client(configuration, factory, writer);
	SimpleWordMapper mapper;
    Benchmark benchmark;
    benchmark.start();
	client.run_job(mapper);
    std::cout << "Elapsed time in second:" << benchmark.end() << std::endl;
}


void create_file(int count_of_M_bytes, const char* file) {
	DiskReader reader(DATA_WITH_4_LINE);
	uint_64 seed_size = reader.get_total_size();
	char* buffer = new char[seed_size];
	reader.read(buffer, 0, seed_size);

	uint_64 mbytes = 1024 * 1024;
	uint_64 count_to_write = mbytes * count_of_M_bytes / (uint_64)seed_size;
	FILE* target_file = fopen(file, "a+");
	while(count_to_write > 0) {
		fwrite(buffer, 1, seed_size, target_file);
		count_to_write--;
	}
	fclose(target_file);
}

TEST_F(PerformanceTest, DISABLED_creates_a_11_G_bytes_file) {
	create_file(11 * 1024, GBYTES11FILE);
}


