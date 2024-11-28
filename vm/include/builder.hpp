#ifndef BUILDER
#define BUILDER

#include <cstddef>
#include <cstdint>

class Builder {
   private:
    void createLoad(uint64_t value);
    void createStore(uint8_t index);
    void createAdd();
    void createInc();
    void createSub();
    void createMul();
    void createDiv();
    void createRet();
    void createCmpGt();
    void createInvoke();

   public: // bytecode init for all expected create<OPCODE> 
    Builder(uint8_t *bytecode, size_t size = 0) : m_bytecode{bytecode}, m_size(size) {}

   private:
    uint8_t *m_bytecode;
    size_t m_size;
};

#endif
