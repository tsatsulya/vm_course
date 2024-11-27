#include "executor.hpp"

#include <assert.h>

#include "bytecode.hpp"
#include "frame.hpp"
#include "method.hpp"

void Executor::execute(Method *func, uint64_t *args, uint16_t num_args) {
    Frame frame(func, &frame_vector.back());
    frame_vector.push_back(frame);

    // push args on stack

    while (executeInstr(frame)) {
        frame.inc_pc();
    }
}

bool Executor::executeInstr(Frame &frame) {
    auto instr = static_cast<Opcode>(frame.getInstr(frame.get_pc()));
    switch (instr) {
        case Opcode::LOAD: {
            executeLoad(frame);
            break;
        }
        case Opcode::ADD: {
            executeAdd(frame);
            break;
        }
        case Opcode::INC: {
            executeInc(frame);
            break;
        }
        case Opcode::SUB: {
            executeSub(frame);
            break;
        }
        case Opcode::MUL: {
            executeMul(frame);
            break;
        }
        case Opcode::DIV: {
            executeDiv(frame);
            break;
        }
        case Opcode::RET: {
            executeRet(frame);
            break; // return False;
        }
        case Opcode::CMP_GT: {
            executeCmpGt(frame);
            break;
        }
        case Opcode::INVOKE: {
            executeInvoke(frame);
            break; // return False;
        }
        default: {
            assert(0 && "Stop on unrecognized instruction opcode");
        }
    }

    return 1;
}

void Executor::executeAdd(Frame &frame) {
    auto val1 = frame.stack_pop();
    auto val2 = frame.stack_pop();
    frame.stack_push(val1 + val2);
}

void Executor::executeInc(Frame &frame) {
    auto val = frame.stack_pop();
    frame.stack_push(val + 1);
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
