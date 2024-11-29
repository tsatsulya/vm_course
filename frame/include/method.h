#ifndef VM_METHOD
#define VM_METHOD

#include <iostream>

#include "instruction.h"

#include <cstddef>
#include <cstdint>
#include <cassert>
#include <vector>
#include <unordered_map>

using namespace instruction;

using offset_t = uint32_t;
using param_t = uint32_t;

class method {
    const char *name;
    offset_t offset;
    size_t args_count;
    size_t params_count = 1;
    // std::vector<inst*> body;
    std::vector<inst> body;
    std::unordered_map<mark_t, size_t> mark_table = {};

public:
    method(const char *name_) : name(name_), body({}) {}

    method(const char *name_, std::vector<inst> &body_) : name(name_), body(body_) {
        params_count = get_local_var_count();
        std::cout << "\nname " << name << " count " << params_count << std::endl;
    }

    method(const char *name_, std::vector<raw_inst_t> &raw_body) : name(name_) {
        for (auto &raw_inst : raw_body) {
            body.push_back(inst(raw_inst));
        }
    }

    reg_idx get_local_var_count() {
        reg_idx max_ind = 0;
        for (inst &i : body) {
            if (i.opcode == opcode_table::lda || i.opcode == opcode_table::sta) {
                assert(i.params.size() == 1);
                max_ind = std::max(max_ind, i.params[0]);
            }
        }
        return max_ind + 1;
    }

    void collect_func_info() {
        size_t p_c = 0;
        for (auto &i : body) {
            if (i.opcode == opcode_table::sign) {
                mark_table[i.mark] = p_c++;
            }
        }
    }

    void add_inst(raw_inst_t &raw_inst) {
        body.push_back(inst(raw_inst));
    }

    void add_inst(inst &new_inst) { body.push_back(new_inst); }

    size_t get_params_count() {
        return params_count;
    }

    inst get_inst(offset_t idx) {
        return body[idx];
    }

    size_t get_size() {
        return body.size();
    }

    void add_mark(mark_t &mark, size_t &pc) {
        mark_table[mark] = pc;
    }
    const char *get_name() { return name; }
};

#endif // VM_METHOD