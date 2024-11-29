#ifndef VM_FRAME
#define VM_FRAME

#include <vector>
#include "bytecode.h"
#include "stack.h"
#include "method.h"
#include "instruction.h"

class frame {
    method *callable;
    size_t num_of_loc_params;
    reg_t * local_variables;

    stack_raw<reg_t> *mem_stack;
    offset_t program_counter = 0;

    frame *prev;
public:

    void set_arg(size_t idx, reg_t value) {
        if (idx >= num_of_loc_params) {
            return;
        }
        local_variables[idx] = value;
    }

    frame(method *callable_, stack_raw<reg_t> *mem_stack_, frame *prev_, reg_t *local_variables_)
        : callable(callable_), mem_stack(mem_stack_), prev(prev_), local_variables(local_variables_) {}

    frame *get_prev() { return prev; }
    method *get_method() { return callable; }
    reg_t *get_mem() { return local_variables; }


    reg_t get_var(size_t &idx) {
        if (idx >= callable->get_params_amount()) {
            return 0;
        }
        return local_variables[idx];
    }

    inst *get_next_inst() {
        return callable->get_inst(program_counter++);
    }
};

#endif // VM_FRAME
