#include "using_bytes.h"
#include "disk_reader.h"

using namespace UTSample;

class DiskReaderTest : public UsingBytes {
};

TEST_F(DiskReaderTest, it_reads_bytes_from_given_file) {
	DiskReader disk_reader(FILE_WITH_27_BYTES);
	char buffer[27];
	size_t read_size = disk_reader.read(buffer, 0, 27);
	ASSERT_EQ(27, read_size);
}

TEST_F(DiskReaderTest, it_reads_bytes_by_offset_and_count) {
	DiskReader disk_reader(FILE_WITH_27_BYTES);
	char buffer[7];
	disk_reader.read(buffer, 20, 7);
	ASSERT_TEXT("CDEFGH\n", buffer, 7);
}

TEST_F(DiskReaderTest, it_returns_0_if_file_not_found) {
	DiskReader disk_reader("file_not_exists");
	char buffer[1];
	long read_size = disk_reader.read(buffer, 0, 1);
	ASSERT_EQ(0, read_size);
}

TEST_F(DiskReaderTest, it_handles_read_out_of_end) {
	DiskReader disk_reader(FILE_WITH_27_BYTES);
	char buffer[1];
	size_t read_count = disk_reader.read(buffer, 26, 10);
	ASSERT_EQ(1, read_count);
	ASSERT_TEXT("\n", buffer, 1);
}

