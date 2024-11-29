#ifndef MACHINE
#define MACHINE

#include <vector>

#include "method.hpp"

class VMMachine {
   private:
    std::vector<Method> functions;
    std::vector<uint8_t> bytecode;

    void load_fibonachi_cycle();
   public:
    VMMachine() {}
    
    void run_fibonachi();
};

#endif
