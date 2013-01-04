#include "disk_hammal_factory.h"
namespace UTSample {

uint_64 DiskHammalFactory::job_size() {
    DiskReader reader(file);
    return reader.get_total_size();
}

Reader* DiskHammalFactory::create_reader() {
    return new DiskReader(file);
}

}

