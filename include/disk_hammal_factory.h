#ifndef __UT_SAMPLE_DISK_HAMMAL_FACTORY__
#define __UT_SAMPLE_DISK_HAMMAL_FACTORY__
#include "disk_reader.h"
#include "hammal_factory.h"
namespace UTSample {
class DiskHammalFactory: public HammalFactory {
public:
    DiskHammalFactory(const char* file) : file(file)  {}
    uint_64 job_size();

protected:
    Reader* create_reader();

private:
    const char* file;
};
}
#endif
