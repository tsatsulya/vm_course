#include "executor.hpp"

#include <assert.h>

#include "bytecode.hpp"
#include "frame.hpp"
#include "method.hpp"

void Executor::execute(Method *func, uint64_t *args, size_t num_args) {
    Frame frame(func, args, num_args, &frame_vector.back());
    frame_vector.push_back(frame);

    // push args on stack
    for (size_t i = 0; i != num_args; ++i) {
        frame.stack_push(args[i]);
    }

    while (executeInstr(frame)) {
    }
}

bool Executor::executeInstr(Frame &frame) {
    auto instr = static_cast<Opcode>(frame.getInstr<uint8_t>(frame.get_pc()));
    switch (instr) {
        case Opcode::LOAD: {
            frame.inc_pc(1);
            auto load_val = frame.getInstr<uint64_t>(frame.get_pc());

            executeLoad(frame, load_val);
            frame.inc_pc(8);
            break;
        }
        case Opcode::STORE: {
            frame.inc_pc(1);
            auto store_index = frame.getInstr<uint8_t>(frame.get_pc());
            
            executeStore(frame, frame.stack_pop());
            frame.inc_pc(1);
            break;
        }
        case Opcode::ADD: {
            executeAdd(frame);
            frame.inc_pc(1);
            break;
        }
        case Opcode::INC: {
            executeInc(frame);
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
            break;  // return False;
        }
        case Opcode::CMP_GT: {
            executeCmpGt(frame);
            break;
        }
        case Opcode::INVOKE: {
            executeInvoke(frame);
            break;  // return False;
        }
        default: {
            assert(0 && "Stop on unrecognized instruction opcode");
        }
    }

    return 1;
}

void Executor::executeLoad(Frame &frame, uint64_t val) { frame.stack_push(val); }

void Executor::executeStore(Frame &frame, uint8_t index) {
    assert(index < frame.getNumArgs() && "Store index out of range");
    frame.storeArg(frame.stack_pop(), index);
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
