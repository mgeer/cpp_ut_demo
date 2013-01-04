#include "using_bytes.h"
#include "output_writer.h"
#include "disk_reader.h"
using namespace UTSample;

static const char* OUTPUT_FILE = "test_output_writer";
class OutputWriterTest : public UsingBytes {
};

TEST_F(OutputWriterTest, it_writes_output_to_given_file) {
	Output output;
	output.total_word_count = 100;
	Term basic1("basic1%@#%", 6);
	Term basic2("basic2^*&(^", 6);
	output.basic_words[basic1] = 10;
	output.basic_words[basic2] = 20;

	Term term1("term1", 5);
	Term term2("term2", 5);
	output.terms[term1] = 30;
	output.terms[term2] = 40;
	OutputWriter writer(OUTPUT_FILE);
	writer.write(output);

	DiskReader reader(OUTPUT_FILE);
	size_t file_size = reader.get_total_size();
	char* buffer = new char[file_size];
	reader.read(buffer, 0, file_size);
	ASSERT_TEXT("basic words:\nbasic1(10/100)\tbasic2(20/100)\t\nterms:\nterm1(30/100)\tterm2(40/100)\t", 
            buffer, file_size);
	delete[] buffer;
}

