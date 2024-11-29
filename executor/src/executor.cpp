#include "executor.h"
#include "bytecode.h"

void executor::execute_inst(inst *i) {
    switch (i->opcode) {
        case opcode_table::lda : {
            // assert
            size_t id = i->params[0];
            mem_stack->push(current_frame->get_var(id));
            break;
            }

        case opcode_table::sta : {
            // assert
            reg_t value = mem_stack->pop();
            size_t id = i->params[0];
            current_frame->set_arg(id, value);
            break;
            }

        case opcode_table::lda_imm : {
            reg_t imm = i->params[0];
            std::cout << "load to stack: " << imm << "\n";
            mem_stack->push(imm);
            break;
            }

        case opcode_table::call0 : {
            assert(i->params[0]);
            create_frame(func_table[i->params[0]]);
            break;
            }

        case opcode_table::ret : {
            std::cout << "return";
            delete_frame();
            break;
            }
        case opcode_table::add : {
            auto imm1 = mem_stack->pop();
            auto imm2 = mem_stack->pop();
            std::cout << "add " << imm1 << " " << imm2 << "\n";
            mem_stack->push(imm1 + imm2);
            break;
            }
        default:
            return;
    }
}