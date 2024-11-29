#include "bytecode.h"
#include "executor.h"
#include "arena/arena.h"
#include <iostream>

int main() {

    inst ret = inst(opcode_table::ret);
    inst lda_imm1 = inst(opcode_table::lda_imm, {1});
    inst lda_imm0 = inst(opcode_table::lda_imm, {0});
    inst lda_imm10 = inst(opcode_table::lda_imm, {10});
    // inst load1_marked = inst(opcode_table::lda_imm, {1}, 1);

    inst lda0 = inst(opcode_table::lda, {0});
    inst lda1 = inst(opcode_table::lda, {1});
    inst lda2 = inst(opcode_table::lda, {2});
    inst lda3 = inst(opcode_table::lda, {3});
    inst lda4 = inst(opcode_table::lda, {4});


    inst sta0 = inst(opcode_table::sta, {0});
    inst sta1 = inst(opcode_table::sta, {1});
    inst sta2 = inst(opcode_table::sta, {2});
    inst sta3 = inst(opcode_table::sta, {3});
    inst sta4 = inst(opcode_table::sta, {4});

    inst print = inst(opcode_table::print, {});
    inst add = inst(opcode_table::add);
    inst jmp_eq23 = inst(opcode_table::jump_eq, {23});
    inst jmp = inst(opcode_table::jump, {8});
    inst incr = inst(opcode_table::incr, {2});

    std::vector<inst> foo_body = {
        lda_imm0,
        sta0,
        lda_imm1,
        sta1,
        lda_imm0,
        sta2,
        lda_imm10,
        sta3,

        lda2,
        lda3,
        jmp_eq23,

        lda0,
        lda1,
        add,
        sta4,
        lda4,
        print,
        lda1,
        sta0,
        lda4,
        sta1,
        incr,
        jmp,
        ret
    };

    method func("foo", foo_body);


    method main_method("main");

    inst call = inst(opcode_table::call0, {2});


    main_method.add_inst(call);
    main_method.add_inst(ret);

    FixedBufferResource buffer(1024 * 10); // 10 KB buffer
    executor m = executor(&buffer, &main_method);
    m.add_func_to_table(2, &func);
    m.add_func_to_table(1, &main_method);
    m.run();
}