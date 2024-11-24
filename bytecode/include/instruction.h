#ifndef VM_INSTRUCTION
#define VM_INSTRUCTION

#include <unordered_map>
#include "bytecode.h"

struct inst {
    opcode_t opcode;
    mark_t mark;
    std::unordered_map<reg_idx, reg_t> param_regs;
    reg_t imm;
    bool is_jump;

    void set_imm(reg_t new_imm) {
        imm  = new_imm;
    }
};

#endif // VM_INSTRUCTION