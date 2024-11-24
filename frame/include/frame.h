#ifndef VM_FRAME
#define VM_FRAME

#include <vector>
#include "bytecode.h"
#include "stack.h"
#include "method.h"

class frame {
public:
    method *callable;
    offset_t return_offset;

    stack_raw<reg_t> *mem_stack;
    std::vector<reg_t> local_variables; // custom allocator

    void set_arg(size_t idx, reg_t value) {
        if (idx >= local_variables.size()) {
            return;
        }
        local_variables[idx] = value;
    }

    void store_args() {
        for (int i = callable->get_params_amount() - 1; i >= 0; i--) {
            local_variables[i] = mem_stack->pop();
        }
    }
    frame(method *callable_, stack_raw<reg_t> *mem_stack_, offset_t call_offset)
        : callable(callable_), mem_stack(mem_stack_), return_offset(call_offset) {
        store_args();
    }

    reg_t get_arg(size_t idx) {
        if (idx >= local_variables.size()) {
            return 0;
        }
        return local_variables[idx];
    }

    offset_t get_return_offset() {
        return return_offset;
    }
};

#endif // VM_FRAME
