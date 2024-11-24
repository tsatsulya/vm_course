#include <vector>
#include "frame.h"

class executor {

    const std::vector<inst> program;
    offset_t inst_c = 0;
    stack_raw<reg_t> main_stack;
    bool executed = false;

    stack_raw<frame> frame_stack;
    executor(std::vector<inst> &program_) : program(program_) {
        frame_stack.push(frame());
    }
};