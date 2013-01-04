#include "using_bytes.h"
#include "disk_hammal_factory.h"

using namespace UTSample;

class DiskHammalFactoryTest: public UsingBytes {
};

TEST_F(DiskHammalFactoryTest, it_get_job_size) {
	DiskHammalFactory factory(FILE_WITH_27_BYTES);
	size_t job_size = factory.job_size();
	ASSERT_EQ(27, job_size);
}

TEST_F(DiskHammalFactoryTest, it_creates_hammal_with_disk_reader) {
	DiskHammalFactory factory(FILE_WITH_27_BYTES);
	Segment segment;
	segment.offset = 0;
	segment.size = 20;
	BlockQueue queue(2);
	BufferPool pool(2, 1024);
	Hammal* hammal = factory.create(segment, queue, 1024, pool);
	hammal->start();
	ASSERT_EQ(20, queue.dequeue().size);
	
}
