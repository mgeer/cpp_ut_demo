#ifndef __UT_SAMPLE_OUTPUT_WRITER_H__
#define __UT_SAMPLE_OUTPUT_WRITER_H__
#include <sstream>
#include <fstream>
#include "result.h"
namespace UTSample {
class OutputWriter {
public:
    OutputWriter(const char* file) : file(file) {}
    size_t write(const Output& output);

private:
    const char* file;
};
}
#endif

