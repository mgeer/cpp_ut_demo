#include "using_bytes.h"
#include "job_client.h"
#include "simple_word_mapper.h"
#include "output_writer.h"
#include "disk_hammal_factory.h"
#include "disk_reader.h"
using namespace UTSample;
static const char* RESULT_FILE = "result";

class JobClientTest : public UsingBytes {
protected:
	void assert_result() {
		DiskReader result_reader(RESULT_FILE);
		size_t size = result_reader.get_total_size();
		char* buffer = new char[size];
		result_reader.read(buffer, 0, size);
		std::string expected = 
            "basic words:\nhelloworld(2/6)\t\nterms:\nhello(2/6)\thelloworld(2/6)\tworld(2/6)\t";
		ASSERT_TEXT(expected, buffer, size);
		delete[] buffer;
	}

	void integration(size_t hammal_count, size_t reading_unit_in_byte, 
                        size_t worker_count, size_t block_buffer_count) {
		DiskHammalFactory factory(DATA_WITH_4_LINE);
		OutputWriter writer(RESULT_FILE);
		JobConfiguration configuration(hammal_count, reading_unit_in_byte, worker_count, block_buffer_count);
		JobClient client(configuration, factory, writer);
		SimpleWordMapper mapper;
		client.run_job(mapper);
		assert_result();
	}
};

TEST_F(JobClientTest, it_breaks_if_job_is_not_found) {
	DiskHammalFactory factory("file_not_exist");
	OutputWriter writer("any_file");
	SimpleWordMapper mapper;
	JobClient client(JobConfiguration(1, 1, 1, 1), factory, writer);
	int ret = client.run_job(mapper);
	ASSERT_EQ(-1, ret);
}

//do not use multiple hammal for disk reading:
TEST_F(JobClientTest, test_multiple_hammal) {
	integration(100, 100, 1, 1);
}


TEST_F(JobClientTest, test_single_hammal_and_worker) {
	integration(1, 1000, 1, 2);
}

TEST_F(JobClientTest, test_multiple_worker) {
	integration(1, 100, 5, 5);
}

TEST_F(JobClientTest, test_single_reading_unit) {
	integration(1, 1, 1, 1);
}

