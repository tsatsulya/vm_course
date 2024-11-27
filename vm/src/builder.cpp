#include "builder.hpp"
#include "bytecode.hpp"


void Builder::createLoad() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::LOAD));
}

void Builder::createAdd() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::ADD));
}

void Builder::createInc() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::INC));
}

void Builder::createSub() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::SUB));
}

void Builder::createMul() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::MUL));
}

void Builder::createDiv() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::DIV));
}

void Builder::createRet() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::RET));
}

void Builder::createCmpGt() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::CMP_GT));
}

void Builder::createInvoke() {
    m_bytecode.push_back(static_cast<opcode_t>(Opcode::INVOKE));
}
