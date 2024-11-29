#ifndef VM_INSTRUCTION
#define VM_INSTRUCTION

#include <vector>
#include "bytecode.h"

using raw_inst_t = uint8_t;

struct inst {
    inst(enum opcode_table opcode_, std::vector<reg_t> params_) : opcode(opcode_), params(params_) {}
    inst(enum opcode_table opcode_) : opcode(opcode_), params({}) {}
    enum opcode_table opcode;
    mark_t mark;
    std::vector<reg_t> params;
    reg_t imm;
    bool is_jump;
};

#endif // VM_INSTRUCTION