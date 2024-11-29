#ifndef VM_INSTRUCTION
#define VM_INSTRUCTION

#include <vector>
#include <set>
#include "bytecode.h"


namespace instruction {

using raw_inst_t = uint32_t;

#define ARG_BITS 10 // Number of bits allocated for argument
#define INSTR_BITS 5 // Number of bits allocated for instruction
#define MAX_ARGS ((1U << ARG_BITS) - 1) // Maximum value for argument

static std::set<enum opcode_table> jumps = { opcode_table::ret,
    opcode_table::jump,
    opcode_table::jump_gg,
    opcode_table::jump_ll,
    opcode_table::jump_eq,
    opcode_table::jump_neq };

struct inst {

    inst(enum opcode_table opcode_, std::vector<reg_t> params_) : opcode(opcode_),
        params(params_), params_count(params_.size()) {}

    inst(raw_inst_t encoded) {
        opcode = (enum opcode_table)((encoded >> ARG_BITS) & ((1U << INSTR_BITS) - 1));
        reg_t argument = encoded & MAX_ARGS;
        params = {argument};
        params_count = 1;
        is_jump = (jumps.find(opcode) == jumps.end());
    }

    raw_inst_t encode() {
        raw_inst_t encoded = 0;
        encoded |= ((int)opcode & ((1U << INSTR_BITS) - 1)) << ARG_BITS;
        encoded |= (params[0] & MAX_ARGS);

        return encoded;
    }

    inst(enum opcode_table opcode_) : opcode(opcode_), params({}), params_count(0) {}
    inst(enum opcode_table opcode_, std::vector<reg_t> params_, mark_t mark_) : opcode(opcode_), params(params_), params_count(params_.size()), mark(mark_) {}

    size_t params_count;
    enum opcode_table opcode;
    mark_t mark;
    std::vector<reg_t> params;
    reg_t imm;
    bool is_jump;
};

} // instruction

#endif // VM_INSTRUCTION