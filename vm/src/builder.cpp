#include "builder.hpp"
#include "bytecode.hpp"

void Builder::createLoad(uint64_t value) { // 1b Opcode::LOAD + 8b value
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::LOAD);
    *(uint64_t*)(m_bytecode + m_size) = value;
    m_size += 8;
}

void Builder::createStore(uint8_t index) { // 1b Opcode::STORE + 1b index
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::STORE);
    m_bytecode[m_size++] = index;
}

void Builder::createAdd() { // 1b Opcode::ADD
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::ADD);
}

void Builder::createInc() { // 1b Opcode::INC
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::INC);
}

void Builder::createSub() { // 1b Opcode::SUB
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::SUB);
}

void Builder::createMul() { // 1b Opcode::MUL
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::MUL);
}

void Builder::createDiv() { // 1b Opcode::DIV
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::DIV);
}

void Builder::createRet() { // 1b Opcode::RET
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::RET);
}

void Builder::createCmpGt() { // 1b Opcode::CmpGt
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::CMP_GT);
}

void Builder::createInvoke() { // 1b Opcode::Invoke
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::INVOKE);
}
