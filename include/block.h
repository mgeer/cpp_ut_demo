#ifndef __UT_SAMPLE_BLOCK_H__
#define __UT_SAMPLE_BLOCK_H__
#include <string>
namespace UTSample {
struct Block {
    Block() : id(0), size(0) {}
    Block(size_t id, const char* buffer, size_t size) 
        : id(id), buffer(buffer), size(size) {}

    size_t id;
    const char* buffer;
    size_t size;
    bool empty() {
        return 0 == size;
    }	
};
}
#endif

