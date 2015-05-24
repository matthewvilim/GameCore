/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H

typedef uint8_t byte_t;
typedef uint16_t word_t;

typedef char reg_t;

typedef struct reg_file {
    // general purpose registers
    word_t gen[8];
    // segment registers
    word_t seg[4];
    // instruction pointer
    word_t ip;
    // flags
    word_t flags;
} reg_file_t;

typedef union operand {
    reg_t reg;
    word_t addr;
} operand_t;

typedef struct decode {
    // linear instruction address from IP and CS
    lin_addr_t instr;
    size_t prefix_len;
    size_t instr_len;
    
    // prefixes
    byte_t prefix_instr;
    byte_t prefix_seg;
    // operands
    operand_t src;
    operand_t dst;
    
} decode_t;

typedef struct cpu {
    reg_file_t reg_file;
    
    decode_t decode;
    
    mem_t *mem;
} cpu_t;

#endif