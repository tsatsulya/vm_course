#include "machine.hpp"
#include "executor.hpp"

#include "builder.hpp"

void VMMachine::load_fibonachi_cycle() {
    bytecode.resize(69);
    Builder builder(bytecode.data());

    builder.createIPush(0); // 0
    builder.createStore(0); // 9
    builder.createIPush(1); // 11
    builder.createStore(1); // 20

    builder.createIPush(0); // 22
    builder.createStore(2); // 31
    builder.createLoad(2); //  33  goto target
    builder.createIPush(10); // 35
    builder.createCmpGe(68); // 44 branch on return

    builder.createLoad(0); // 47
    builder.createLoad(1); // 49
    builder.createAdd(); // 51
    builder.createStore(3); // 52

    builder.createLoad(1); // 54
    builder.createStore(0); // 56

    builder.createLoad(3); // 58
    builder.createStore(1); // 60

    builder.createInc(2, 1); // 62
    builder.createGoto(33); // 65

    builder.createRet(); // 69
}

void VMMachine::run_fibonachi() {
    Executor executor{};

    load_fibonachi_cycle();
    Method fibonachi(bytecode.data(), bytecode.size());

    for (size_t i = 0; i != bytecode.size(); ++i) {
        std::cout << (uint64_t) bytecode[i] << " ";
    }

    executor.execute(&fibonachi, NULL, 0, 4);
}

