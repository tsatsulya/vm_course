#include <vector>
#include "frame.h"

class executor {

    const std::vector<inst> program;
    offset_t inst_c = 0;
    stack_raw<reg_t> mem_stack;
    bool terminated = false;

    stack_raw<frame> frame_stack;
    executor(std::vector<inst> &program_) : program(program_) {
        // assert(program.size()) D:
        // stasks size??
        frame_stack.push(frame());
    }

    offset_t get_inst_c() const {
        return inst_c;
    }

    stack_raw<reg_t> get_mem_stack() const {
        return mem_stack;
    }

    bool is_terminated() const {
        return terminated;
    }

    inst get_next_inst() {
        if (inst_c >= program.size()) {
            return inst();
        }
        return program[++inst_c];
    }

    // inst decode_inst !!!!!!!!!!
    // void execute_inst !!!!!!!!!!
    void iterate() {
        if (terminated) { return; }
        inst next_inst = get_next_inst();
        if (next_inst.opcode == (opcode_t)opcode_table::terminate) {
            terminated = true;
        }
        // execute_inst
    }

    void run() {
        while (!terminated) {
            iterate();
        }
    }
};