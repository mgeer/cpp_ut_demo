#ifndef __UT_SAMPLE_TASK_H__
#define __UT_SAMPLE_TASK_H__
#include "block.h"
#include "mapper.h"
#include "result.h"
namespace UTSample {
class Task {
public:
    void map(Block& block, Mapper& mapper, Result& result);

private:
    size_t save_head(Block& block, Result& result);
    void save_tail(Block& block, size_t tail_start, Result& result);
};
}
#endif

