#ifndef __UT_SAMPLE_DISK_READER_H__
#define __UT_SAMPLE_DISK_READER_H__
#include <fstream>
#include "reader.h"
namespace UTSample {
class DiskReader : public Reader {
public:
    DiskReader(const char* file) : file(file) {}

    virtual size_t read(char* buffer, size_t offset, size_t count);
    virtual uint_64 get_total_size();

private:
    const char* file;
};
}
#endif

