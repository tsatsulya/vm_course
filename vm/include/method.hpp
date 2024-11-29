#ifndef VM_METHOD
#define VM_METHOD

#include <cstddef>
#include <assert.h>

#include <iostream>

#include "bytecode.hpp"

using offset_t = uint32_t;
using param_t = uint32_t;

class Method {
   private:
    // meta_t meta
    uint8_t *m_bytecode;
    size_t m_size;

   public:
    Method(uint8_t *bytecode, size_t size) : m_bytecode(bytecode), m_size(size) {}

    template <typename Type>
    [[nodiscard]] Type getInstr(uint32_t ip) {
        std::cout << "ip: " << ip << std::endl; 
        assert(ip < m_size && "Instruction pointer out out of range");
        return *reinterpret_cast<Type*>(m_bytecode + ip);
    }
};

#endif  // VM_METHOD