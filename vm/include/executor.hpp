#ifndef EXECUTOR
#define EXECUTOR

#include <cstdint>
#include <vector>

#include "method.hpp"
#include "frame.hpp"

class Executor {
   private:
    std::vector<Frame> frame_vector;

    bool executeInstr(Frame &frame);

    void executeLoad(Frame &frame);
    void executeAdd(Frame &frrame);
    void executeInc(Frame &frame);
    void executeSub(Frame &frame);
    void executeMul(Frame &frame);
    void executeDiv(Frame &frame);
    void executeRet(Frame &frame);
    void executeCmpGt(Frame &frame);
    void executeInvoke(Frame &frame);

   public:
    Executor() {}

    void execute(Method *func, uint64_t *args, uint16_t num_args);
};

#endif // EXECUTOR