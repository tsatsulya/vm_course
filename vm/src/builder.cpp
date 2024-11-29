#include "builder.hpp"

#include "bytecode.hpp"

void Builder::createLoad(uint8_t index) {  // 1b Opcode::LOAD + 1b index
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::LOAD);
    m_bytecode[m_size++] = index;
}

void Builder::createStore(uint8_t index) {  // 1b Opcode::STORE + 1b index
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::STORE);
    m_bytecode[m_size++] = index;
}

void Builder::createIPush(uint64_t value) { // 9b
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::IPUSH);
    *(uint64_t*)(m_bytecode + m_size) = value;
    m_size += 8;
}

void Builder::createAdd() {  // 1b Opcode::ADD
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::ADD);
}

void Builder::createInc(uint8_t index, int8_t value) {  // 3b
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::INC);
    m_bytecode[m_size++] = index;
    m_bytecode[m_size++] = value;
}

void Builder::createSub() {  // 1b Opcode::SUB
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::SUB);
}

void Builder::createMul() {  // 1b Opcode::MUL
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::MUL);
}

void Builder::createDiv() {  // 1b Opcode::DIV
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::DIV);
}

void Builder::createRet() {  // 1b Opcode::RET
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::RET);
}

void Builder::createCmpGe(uint16_t branch_offset) { // 3b
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::CMP_GE);
    *(uint16_t*)(m_bytecode + m_size) = branch_offset;
    m_size += 2;
}

void Builder::createCmpGt(uint16_t branch_offset) {  // 3b
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::CMP_GT);
    *(uint16_t*)(m_bytecode + m_size) = branch_offset;
    m_size += 2;
}

void Builder::createGoto(uint16_t branch_offset) {  // 3b
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::GOTO);
    *(uint16_t*)(m_bytecode + m_size) = branch_offset;
    m_size += 2;
}

void Builder::createInvoke() {  // 1b Opcode::Invoke
    m_bytecode[m_size++] = static_cast<opcode_t>(Opcode::INVOKE);
}
