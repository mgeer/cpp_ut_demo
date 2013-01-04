#ifndef __UT_SAMPLE_HAMMAL_FACTORY__
#define __UT_SAMPLE_HAMMAL_FACTORY__
#include "hammal.h"
namespace UTSample {
class HammalFactory {
public:
    HammalFactory() : hammals(), readers() {}

    virtual ~HammalFactory() {
        for( size_t i = 0; i < hammals.size(); i++ ) {
            delete hammals[i];
        }
        for( size_t i = 0; i < readers.size(); i++ ) {
            delete readers[i];
        }
    }

public:
    Hammal* create(Segment segment, BlockQueue& queue, size_t reading_unit, 
            BufferPool& pool) {
        Reader* reader = create_reader();
        Hammal* hammal = new Hammal(segment, *reader, queue, reading_unit, pool);
        readers.push_back(reader);
        hammals.push_back(hammal);
        return hammal;
    }

    virtual uint_64 job_size() = 0;

protected:
    virtual Reader* create_reader() = 0;

private:
    std::vector<Hammal*> hammals;
    std::vector<Reader*> readers;
};
}
#endif

