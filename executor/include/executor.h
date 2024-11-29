#include <cstdint>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "instruction.h"
#include "frame.h"
#include "method.h"
#include "arena/arena.h"
#include "stack.h"

class executor {

    const std::vector<inst> program;
    offset_t inst_c = 0;
    stack_raw<reg_t> *mem_stack;
    std::unordered_map<int32_t, method*> func_table = {};

    bool terminated = false;
    frame *frames[64];
    size_t frame_count = 0;

    frame *current_frame = nullptr;
    method *current_method = nullptr;
    arena arena_resource;

public:
    executor(method *entry_method) : arena_resource(arena(2048)) {
        mem_stack = new stack_raw<reg_t>(5);
        create_frame(entry_method);
    }

    void create_frame(method *callable) {
        current_method = callable;
        reg_t *frame_mem = arena_resource.get_allocator().allocate(current_method->get_params_amount());
        frames[frame_count++] = new frame(callable, mem_stack, current_frame, frame_mem);
        current_frame = frames[frame_count - 1];
    }

    void delete_frame() {
        current_frame = current_frame->get_prev();
        delete frames[frame_count - 1];

        if (!current_frame) {
            terminated = true;
            return;
        }
        current_method = current_frame->get_method();
    }

    void add_func_to_table(int32_t id, method *f) {
        func_table[id] = f;
    }

    offset_t get_inst_c() const {
        return inst_c;
    }

    stack_raw<reg_t> *get_mem_stack() const {
        return mem_stack;
    }

    void execute_inst(inst *i);
    void run() {
        while (!terminated) {
            iterate();
        }
    }

private:
    void iterate() {
        if (terminated) {
            return;
        }
        inst *next_inst = current_frame->get_next_inst();
        if (next_inst->opcode == opcode_table::terminate) {
            terminated = true;
        }
        execute_inst(next_inst);
    }

};