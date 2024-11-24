#include <cstdint>
#include <vector>
#include "frame.h"
#include "instruction.h"
#include <unordered_map>

class executor {

    const std::vector<inst> program;
    offset_t inst_c = 0;
    stack_raw<reg_t> mem_stack;

    bool terminated = false;
    stack_raw<frame> frame_stack;
    frame current_frame;

    std::unordered_map<int32_t, method*> func_table;
    executor(std::vector<inst> &program_) : program(program_) {
        // assert(program.size()) D:
        frame_stack = stack_raw<frame>(64);
        current_frame = frame();
        frame_stack.push(current_frame);
    }

    void add_func_to_table(int32_t id, method *f) {
        func_table[id] = f;
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

    void execute_inst(inst i);

    void iterate() {
        if (terminated) {
            return;
        }
        inst next_inst = get_next_inst();
        if (next_inst.opcode == opcode_table::terminate) {
            terminated = true;
        }
        execute_inst(program[inst_c]);
    }

    void run() {
        while (!terminated) {
            iterate();
        }
    }

};