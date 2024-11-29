#ifndef EXECUTOR
#define EXECUTOR

#include <cstdint>
#include <vector>

#include "frame.hpp"
#include "method.hpp"

class Executor {
   private:
    std::vector<Frame> frame_vector;

    bool executeInstr(Frame &frame);

    void executeLoad(Frame &frame, uint8_t index);
    void executeStore(Frame &frame, uint8_t index);

    void executeIPush(Frame &frame, uint64_t value);

    void executeAdd(Frame &frrame);

    void executeInc(Frame &frame, uint8_t index, uint8_t value);

    void executeSub(Frame &frame);
    void executeMul(Frame &frame);
    void executeDiv(Frame &frame);
    void executeRet(Frame &frame);

    void executeCmpGe(Frame &frame, uint16_t branch_offset);
    void executeCmpGt(Frame &frame, uint16_t branch_offset);

    void executeGoto(Frame &frame, uint16_t branch_offset);

    void executeInvoke(Frame &frame);

   public:
    Executor() {}

    void execute(Method *func, uint64_t *args, size_t num_args, size_t num_local);
};

#endif  // EXECUTOR