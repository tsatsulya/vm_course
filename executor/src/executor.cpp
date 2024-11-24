#include "executor.h"
#include "bytecode.h"

void executor::execute_inst(inst i) {
    switch (i.opcode) {
        case opcode_table::lda : {
            // assert
            size_t id = i.params[0];
            mem_stack.push(frame_stack.get_head().get_var(id));
            }
            break;

        case opcode_table::sta : {
            // assert
            reg_t value = mem_stack.pop();
            size_t id = i.params[0];
            current_frame.set_arg(id, value);
            }
            break;

        case opcode_table::lda_imm : {
            reg_t imm = i.params[0];
            mem_stack.push(imm);
            }
            break;

        default:
            return;
    }
}