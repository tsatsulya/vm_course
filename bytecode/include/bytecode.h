#ifndef VM_BYTECODE
#define VM_BYTECODE

#include <cstdint>

using reg_idx = uint64_t;
using reg_t = uint64_t;
using opcode_t = uint8_t;
using mark_t = uint8_t;

enum class opcode_table : opcode_t
{
    lda,
    lda_imm,
    sta,
    mov,
    mov_imm,
    add,
    sub,
    mod,
    div,
    mul,
    ret,
    jump,
    jump_gg,
    jump_ll,
    jump_eq,
    jump_neq,
    call0,
    call1,
    call2,
    cmp_eq,
    cmp_gg,
    cmp_ll,
    terminate,
    sign,
    incr,
    decr,
    print,
    print_imm,
};


#endif  // VM_BYTECODE


