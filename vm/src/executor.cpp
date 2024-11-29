#include "executor.hpp"

#include <assert.h>

#include <iostream>

#include "bytecode.hpp"
#include "frame.hpp"
#include "method.hpp"

void Executor::execute(Method *func, uint64_t *start_args, size_t start_num_args,
                       size_t num_locals) {
    Frame frame(func, num_locals, &frame_vector.back());
    frame_vector.push_back(frame);

    // push args on stack
    for (size_t i = 0; i != start_num_args; ++i) {
        frame.stack_push(start_args[i]);
    }

    while (executeInstr(frame)) {
        frame.dump_variables();
    }
}

bool Executor::executeInstr(Frame &frame) {
    auto instr = static_cast<Opcode>(frame.getInstr<uint8_t>(frame.get_pc()));
    switch (instr) {
        case Opcode::LOAD: {
            frame.inc_pc(1);
            auto load_index = frame.getInstr<uint8_t>(frame.get_pc());
            executeLoad(frame, load_index);

            frame.inc_pc(1);
            break;
        }
        case Opcode::STORE: {
            frame.inc_pc(1);
            auto store_index = frame.getInstr<uint8_t>(frame.get_pc());
            executeStore(frame, store_index);

            frame.inc_pc(1);
            break;
        }
        case Opcode::IPUSH: {
            frame.inc_pc(1);
            auto push_val = frame.getInstr<uint64_t>(frame.get_pc());
            executeIPush(frame, push_val);

            frame.inc_pc(8);
            break;
        }
        case Opcode::ADD: {
            executeAdd(frame);
            frame.inc_pc(1);
            break;
        }
        case Opcode::INC: {
            frame.inc_pc(1);
            auto index = frame.getInstr<uint8_t>(frame.get_pc());
            frame.inc_pc(1);
            auto value = frame.getInstr<uint8_t>(frame.get_pc());

            executeInc(frame, index, value);
            frame.inc_pc(1);
            break;
        }
        case Opcode::SUB: {
            executeSub(frame);
            frame.inc_pc(1);
            break;
        }
        case Opcode::MUL: {
            executeMul(frame);
            frame.inc_pc(1);
            break;
        }
        case Opcode::DIV: {
            executeDiv(frame);
            frame.inc_pc(1);
            break;
        }
        case Opcode::RET: {
            executeRet(frame);
            return 0;  // return False;
        }
        case Opcode::CMP_GE: {
            frame.inc_pc(1);
            auto branch_offset = frame.getInstr<uint16_t>(frame.get_pc());
            executeCmpGe(frame, branch_offset);
            break;
        }
        case Opcode::GOTO: {
            frame.inc_pc(1);
            auto branch_offset = frame.getInstr<uint16_t>(frame.get_pc());
            executeGoto(frame, branch_offset);
            break;
        }
        default: {
            assert(0 && "Stop on unrecognized instruction opcode");
        }
    }

    return 1;
}

void Executor::executeLoad(Frame &frame, uint8_t index) {
    std::cout << (uint64_t)index << " >= " << frame.getNumArgs() << std::endl;
    assert(index < frame.getNumArgs() && "Store index out of range");
    frame.stack_push(frame.loadArg(index));
}

void Executor::executeStore(Frame &frame, uint8_t index) {
    std::cout << (uint64_t)index << " >= " << frame.getNumArgs() << std::endl;
    assert(index < frame.getNumArgs() && "Load index out of range");

    auto val = frame.stack_pop();
    std::cout << "Get from stack: " << val << std::endl;
    frame.storeArg(val, index);
}

void Executor::executeIPush(Frame &frame, uint64_t value) {
    std::cout << "Try push: " << value << std::endl;
    frame.stack_push(value);
}

void Executor::executeAdd(Frame &frame) {
    auto val1 = frame.stack_pop();
    auto val2 = frame.stack_pop();
    frame.stack_push(val1 + val2);
}

void Executor::executeInc(Frame &frame, uint8_t index, uint8_t value) {
    frame.storeArg(frame.loadArg(index) + value, index);
}

void Executor::executeSub(Frame &frame) {
    auto val1 = frame.stack_pop();
    auto val2 = frame.stack_pop();
    frame.stack_push(val2 - val1);
}

void Executor::executeMul(Frame &frame) {
    auto val1 = frame.stack_pop();
    auto val2 = frame.stack_pop();
    frame.stack_push(val1 * val2);
}

void Executor::executeDiv(Frame &frame) {
    auto val1 = frame.stack_pop();
    auto val2 = frame.stack_pop();
    frame.stack_push(val2 / val1);
}

void Executor::executeCmpGe(Frame &frame, uint16_t branch_offset) {
    auto val1 = frame.stack_pop();
    auto val2 = frame.stack_pop();
    std::cout << "CmpGe " << val2 << " >= " << val1 << std::endl;

    if (val2 >= val1) {
        frame.set_pc(branch_offset);
    } else {
        frame.inc_pc(2);
    }
}

void Executor::executeGoto(Frame &frame, uint16_t branch_offset) { frame.set_pc(branch_offset); }

void Executor::executeRet(Frame &frame) {}