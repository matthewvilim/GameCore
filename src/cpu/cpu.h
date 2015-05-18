/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H





// NOTE: Bitfields/unions in C do NOT guarantee ordering, alignment, or endianess and should be avoided
// when mapping to emulated HW registers, so for portability, we use bit mask macros only.

bool static inline
cpu_vm(cpu_t *cpu) {
    return !!(cpu->reg_file.eflags & EFLAG_MASK_VM);
}

dword_t
cpu_reg_read(uint8_t reg, dword_t mask) {
    return cpu->reg_file.
}

typedef enum reg_gen {
    reg_gen_idx_t idx;
    word_t mask;
} reg_gen_t;

// size of operant 
typedef enum operand_size {
    OPERAND_SIZE_BYTE,
    OPERAND_SIZE_WORD,
    OPERAND_SIZE_DWORD
} operand_size_t;

typedef void (*instr_gen_t)(cpu_t *cpu);

typedef struct reg_file {
    // general purpose registers
    dword_t gen[REG_GEN_IDX_LAST];
    // segment registers
    word_t seg[REG_SEG_IDX_LAST];
    // instruction pointer
    dword_t eip;
    // flags
    dword_t eflags;
} reg_file_t;

typedef struct decode {
    op_info_t *op_info;
    byte_t opcode;
    byte_t modrm;
    operant_size_t operant_size;
    operand_t reg, rm;
} decode_t;

typedef void (*decode_func_t)(byte_t, operand_t *, reg_file_t *);

typedef vtable {
    decode_func_t decode;

} vtable_t;

typedef struct cpu {
    reg_file_t reg_file;
    
    instr_gen_t instr_gen;
    decode_t decode;
    
    vtable_t *vtable;
} cpu_t;

C86_INLINE word_t
reg_gen_read(reg_file_t *reg_file, reg_gen_idx_t idx) {
    return MASK_GET_VAL(reg_file->gen[reg->idx], reg->mask);
}

C86_INLINE void
reg_gen_write(reg_file_t *reg_file, reg_gen_t *reg, word_t val) {
    MASK_SET_VAL(reg_file->gen[reg->idx], reg->mask, val);
}

#endif