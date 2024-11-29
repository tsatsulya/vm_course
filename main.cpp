#include "bytecode.h"
#include "executor.h"
#include <iostream>

int main() {
    method main_method("main");
    inst ret = inst(opcode_table::ret);
    inst load1 = inst(opcode_table::lda_imm, {1});
    inst load2= inst(opcode_table::lda_imm, {2});
    inst add = inst(opcode_table::add);

    main_method.add_inst(&load1);
    main_method.add_inst(&load2);
    main_method.add_inst(&add);
    main_method.add_inst(&ret);

    executor m = executor(&main_method);
    m.add_func_to_table(1, &main_method);
    m.run();
}