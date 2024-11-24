#ifndef VM_FRAME
#define VM_FRAME

#include <vector>
#include "bytecode.h"
#include "stack.h"
#include "method.h"

class frame {
    method *callable;
    offset_t return_offset;

    stack_raw<reg_t> *mem_stack;
    std::vector<reg_t> local_variables; // custom allocator

public:

    void set_arg(size_t idx, reg_t value) {
        if (idx >= local_variables.size()) {
            return;
        }
        local_variables[idx] = value;
    }

    frame(method *callable_, stack_raw<reg_t> *mem_stack_, offset_t call_offset)
        : callable(callable_), mem_stack(mem_stack_), return_offset(call_offset) {}

    frame() {}

    reg_t get_var(size_t idx) {
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
