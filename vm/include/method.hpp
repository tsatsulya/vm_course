#ifndef VM_METHOD
#define VM_METHOD

#include <vector>

#include "bytecode.hpp"

using offset_t = uint32_t;
using param_t = uint32_t;

class Method {
   private:
    // meta_t meta
    std::vector<uint8_t> &m_bytecode;

   public:
    Method(std::vector<uint8_t> &bytecode) : m_bytecode{bytecode} {}

    [[nodiscard]] uint8_t getInstr(uint8_t pc) {
        return m_bytecode[pc];
    }
};

#endif  // VM_METHOD