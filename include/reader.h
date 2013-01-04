#ifndef __UT_SAMPLE_READER_H__
#define __UT_SAMPLE_READER_H__
#include <iostream>
#include "def.h"

namespace UTSample {
class Reader {
public:
    virtual size_t read(char* buffer, size_t offset, size_t count) = 0;
    virtual uint_64 get_total_size() = 0;
};
}
#endif

