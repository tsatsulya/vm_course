#ifndef BUILDER
#define BUILDER

#include <cstddef>
#include <cstdint>

class Builder {
   public:
    void createLoad(uint8_t value);
    void createStore(uint8_t index);
    void createIPush(uint64_t value);
    
    void createAdd();

    void createInc(uint8_t index, int8_t value);
    
    void createSub();
    void createMul();
    void createDiv();
    void createRet();

    void createCmpGe(uint16_t branch_offset);
    void createCmpGt(uint16_t branch_offset);

    void createGoto(uint16_t branch_offset);

    void createInvoke();

   public: // bytecode init for all expected create<OPCODE> 
    Builder(uint8_t *bytecode, size_t size = 0) : m_bytecode{bytecode}, m_size(size) {}

   private:
    uint8_t *m_bytecode;
    size_t m_size;
};

#endif
