#include "executor.h"
#include "bytecode.h"

void executor::execute_inst(inst &i) {
    switch (i.opcode) {
        case opcode_table::lda : {
            assert(i.params_count && i.params.size() == 1);
            size_t id = i.params[0];
            std::cout << "lda " << current_frame->get_var(id) << "\n";
            mem_stack->push(current_frame->get_var(id));
            break;
            }

        case opcode_table::sta : {
            assert(i.params_count && i.params.size() == 1);
            reg_t value = mem_stack->pop();
            size_t id = i.params[0];
            std::cout << "sta " << value << " to "<< id << "\n";
            current_frame->set_arg(id, value);
            current_frame->print_local_vars();
            break;
            }

        case opcode_table::lda_imm : {
            assert(i.params_count && i.params.size() == 1);
            reg_t imm = i.params[0];
            std::cout << "lda_imm " << imm << "\n";
            mem_stack->push(imm);
            mem_stack->print();
            break;
            }

        case opcode_table::call0 : {
            assert(i.params_count && i.params.size() == 1);
            std::cout << "\ncall " << func_table[i.params[0]]->get_name() << '\n';
            create_frame(func_table[i.params[0]]);
            break;
            }

        case opcode_table::ret : {
            std::cout << "\nreturn\n\n";
            delete_frame();
            break;
            }

        case opcode_table::add : {
            mem_stack->print();
            auto imm1 = mem_stack->pop();
            auto imm2 = mem_stack->pop();
            // assert(imm1 && imm2);

            std::cout << "add " << imm1 << " " << imm2 << "\n";
            mem_stack->push(imm1 + imm2);
            std::cout << "load to stack " << imm1 + imm2 << "\n";
            mem_stack->print();
            break;
            }

        case opcode_table::sub : {
            mem_stack->print();
            auto imm1 = mem_stack->pop();
            auto imm2 = mem_stack->pop();
            // assert(imm1 && imm2);

            std::cout << "sub " << imm2 << " " << imm1 << "\n";
            mem_stack->push(imm2 - imm1);
            std::cout << "load to stack " << imm2 - imm1 << "\n";
            mem_stack->print();
            break;
            }

        case opcode_table::jump : {
            assert(i.params_count && i.params.size() == 1);
            current_frame->set_pc(i.params[0]);
            std::cout << "\njump to " << i.params[0] << std::endl;
            break;
        }

        case opcode_table::jump_eq : {
            assert(i.params_count && i.params_count == 1);
            auto imm1 = mem_stack->pop();
            auto imm2 = mem_stack->pop();
            // assert(imm1 && imm2);
            std::cout << "\njump to " << i.params[0] << " if " << imm1 << " == " << imm2 << std::endl;

            if (imm1 == imm2) {
                current_frame->set_pc(i.params[0]);
            }
            break;
        }

        case opcode_table::jump_gg : {
            assert(i.params_count && i.params_count == 1);
            auto imm1 = mem_stack->pop();
            auto imm2 = mem_stack->pop();
            // assert(imm1 && imm2);
            if (imm1 > imm2) {
                current_frame->set_pc(i.params[0]);
            }
            break;
        }

        case opcode_table::jump_ll : {
            assert(i.params_count && i.params_count == 1);
            auto imm1 = mem_stack->pop();
            auto imm2 = mem_stack->pop();
            // assert(imm1 && imm2);
            if (imm1 < imm2) {
                current_frame->set_pc(i.params[0]);
            }
            break;
        }

        case opcode_table::incr : {
            assert(i.params_count && i.params_count == 1);
            auto id = i.params[0];
            auto var = current_frame->get_var(id);
            std::cout << "incr " << var << '\n';
            current_frame->set_arg(id, ++var);
            break;
        }

        case opcode_table::decr : {
            assert(i.params_count && i.params_count == 1);
            auto id = i.params[0];
            auto var = current_frame->get_var(id);
            current_frame->set_arg(id, --var);
            break;
        }

        case opcode_table::print : {
            auto val = mem_stack->pop();
            std::cout << "\n>>> " << val << " <<<\n\n";
        }

        // case opcode_table::print_imm : {
        //     assert(i.params_count == 1);
        //     std::cout << i.params[0] << std::endl;
        // }

        default:
            return;
    }
}