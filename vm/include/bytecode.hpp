#ifndef VM_BYTECODE
#define VM_BYTECODE

#include <cstdint>

using reg_idx = uint64_t;
using reg_t = uint64_t;
using opcode_t = uint8_t;
using mark_t = uint8_t;

enum class Opcode : opcode_t {
    LOAD = 0x1,
    ADD = 0x2,
    INC = 0x3,
    SUB = 0x4,
    MUL = 0x5,
    DIV = 0x6,
    RET = 0x7,
    CMP_GT = 0x8,
    INVOKE = 0x9,

    STORE = 0xA,
};

#endif  // VM_BYTECODE