#ifndef BUILDER
#define BUILDER

#include <cstdint>
#include <vector>

class Builder {
   private:
    void createLoad();
    void createAdd();
    void createInc();
    void createSub();
    void createMul();
    void createDiv();
    void createRet();
    void createCmpGt();
    void createInvoke();

   public:
    Builder(std::vector<uint8_t> &bytecode) : m_bytecode{bytecode} {}

   private:
    std::vector<uint8_t> &m_bytecode;
};

#endif
