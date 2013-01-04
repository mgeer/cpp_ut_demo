#include <gtest.h>
#include "buffer_pool.h"
using namespace UTSample;

class BufferPoolTest : public testing::Test {
};

TEST_F(BufferPoolTest, it_creates_buffers) {
	BufferPool pool(2, 1024);
	pool.get_buffer();
	pool.get_buffer();

    //since there are 2 buffer, so call get_buffer twice must be OK,
    //but if call get_buffer again, thread will be hold. 
    //don't know how to ASSERT it here, 
}

