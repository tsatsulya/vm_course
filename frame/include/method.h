#ifndef VM_METHOD
#define VM_METHOD

#include <iostream>

#include "instruction.h"

#include <cstddef>
#include <cstdint>
#include <cassert>
#include <vector>

using offset_t = uint32_t;
using param_t = uint32_t;

class method {
    const char *name;
    offset_t offset;
    size_t params_count = 1;
    std::vector<inst*> body;
public:
    method(const char *name_) : name(name_), body({}) {}

    method(const char *name_, std::vector<inst*> &body_) : name(name_), body(body_) {
        params_count = get_local_var_amount();
    }

    reg_idx get_local_var_amount() {
        reg_idx max_ind = 0;
        for (inst *i : body) {
            if (i->opcode == opcode_table::lda || i->opcode == opcode_table::sta) {
                assert(i->params[0]);
                max_ind = std::max(max_ind, i->params[0]);
            }
        }
        return max_ind + 1;
    }

    inst *decode_inst(raw_inst_t raw_inst);
    void add_inst(raw_inst_t raw_inst) {
        body.push_back(decode_inst(raw_inst));
    }
    void add_inst(inst *new_inst) { body.push_back(new_inst); }

    size_t get_params_amount() {
        return params_count;
    }

    inst *get_inst(offset_t idx) {
        return body[idx];
    }

    size_t get_inst_amount() {
        return body.size();
    }
};

#endif // VM_METHOD