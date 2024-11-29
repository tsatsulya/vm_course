#ifndef VM_FRAME
#define VM_FRAME

#include <vector>
#include "bytecode.h"
#include "stack.h"
#include "method.h"
#include "instruction.h"

using namespace instruction;

class frame {
    method *callable;
    size_t num_of_loc_params;
    offset_t program_counter = 0;
    frame *prev;

    std::pmr::vector<reg_t> local_variables; // Example: local variables stored as integers


public:

    void set_arg(size_t idx, reg_t value) {
        if (idx >= num_of_loc_params) {
            return;
        }
        local_variables[idx] = value;
    }

    std::pmr::vector<int> localVariables; // Vector for local variables

    // Constructor that takes a pointer to an existing vector
    frame(std::pmr::vector<reg_t> *vars, method *callable_, frame *prev_)
        : local_variables(vars->get_allocator()), callable(callable_), prev(prev_) {
        local_variables.swap(*vars);
        num_of_loc_params = local_variables.size();
        callable->collect_func_info();
    }

    void print_local_vars() {
        std::cout << "local nums now: ";
        for (int i = 0; i < num_of_loc_params; i++) {
            std::cout << local_variables[i] << ' ';
        }
        std::cout << "\n";
    }

    frame *get_prev() { return prev; }
    method *get_method() { return callable; }

    void set_pc(size_t pc) {
        if (pc < callable->get_size() && pc >= 0){
            program_counter = pc;
        }
    }

    reg_t get_var(size_t &idx) {
        if (idx >= callable->get_params_count()) {
            return 0;
        }
        return local_variables[idx];
    }

    inst get_next_inst() {
        return callable->get_inst(program_counter++);
    }
};

#endif // VM_FRAME
