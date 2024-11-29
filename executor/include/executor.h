#include <cstdint>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

#include "bytecode.h"
#include "instruction.h"
#include "frame.h"
#include "method.h"
#include "arena/arena.h"
#include "stack.h"

#define FRAME_MAX_COUNT 200
#define ARENA_SPACE 2048


class executor {

    offset_t inst_c = 0;
    stack_raw<reg_t> *mem_stack;
    std::unordered_map<int32_t, method*> func_table = {};


    bool terminated = false;
    frame *frames[FRAME_MAX_COUNT];
    size_t frame_count = 0;

    std::pmr::memory_resource* resource; // Memory resource for allocation
    frame *current_frame = nullptr;

public:
    executor(std::pmr::memory_resource* resource, method *entry_method) : resource(resource) {
        mem_stack = new stack_raw<reg_t>(5);
        create_frame(entry_method);
    }

    void create_frame(method *callable) {
        assert(frame_count < FRAME_MAX_COUNT && "Stack overflow");
        auto numLocalVars = callable->get_local_var_count();
        auto* local_vars = new std::pmr::vector<reg_t>(resource);
        local_vars->resize(numLocalVars);
        frames[frame_count++] = new frame(local_vars, callable, current_frame);
        current_frame = frames[frame_count - 1];
    }

    void delete_frame() {
        current_frame = current_frame->get_prev();

        if (!current_frame) {
            terminated = true;
            return;
        }
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

    void execute_inst(inst &i);

    void run() {
        while (!terminated) {
            iterate();
        }
    }

private:

    void execute_lda();
    void execute_sta();
    void execute_lda_imm();
    void execute_call0();
    void execute_ret();
    void execute_add();
    void execute_sub();
    void execute_jump();
    void execute_jump_eq();
    void execute_jump_gg();
    void execute_jump_ll();
    void execute_incr();
    void execute_decr();
    void execute_print();

    void iterate() {
        if (terminated) {
            return;
        }

        inst next_inst = current_frame->get_next_inst();

        if (next_inst.opcode == opcode_table::terminate) {
            terminated = true;
        }
        execute_inst(next_inst);
    }

};