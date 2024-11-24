#ifndef VM_FRAME
#define VM_FRAME

#include <vector>
#include "instruction.h"
#include "stack.h"
#include "method.h"

class frame {
public:
    method *callable;
    offset_t return_offset;

    stack_raw<frame> *stack;
    std::vector<param_t> local_variables; // custom allocator

    frame *prev  = nullptr;
};

#endif // VM_FRAME
