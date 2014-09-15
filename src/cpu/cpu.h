/**********************************************************************************
 *                                                                                *
 * The MIT License (MIT)                                                          *
 *                                                                                *
 * Core 8086                                                                      *
 * Copyright (c) 2014 Matthew Vilim                                               *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in all *
 * copies or substantial portions of the Software.                                *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 * SOFTWARE.                                                                      *
 *                                                                                *
 **********************************************************************************/

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H

// NOTE: Bitfields/unions in C do NOT guarantee ordering, alignment, or endianess and should be avoided
// when mapping to emulated HW registers, so for portability, we use bit mask macros only.

/******************
 * REGISTER MASKS *
 ******************/

#define FLAG_MASK_CARRY               (0x1 << 0)
#define FLAG_MASK_RESERVED1           (0x1 << 1)
#define FLAG_MASK_PARITY              (0x1 << 2)
#define FLAG_MASK_RESERVED3           (0x1 << 3)
#define FLAG_MASK_ADJUST              (0x1 << 4)
#define FLAG_MASK_RESERVED5           (0x1 << 5)
#define FLAG_MASK_ZERO                (0x1 << 6)
#define FLAG_MASK_SIGN                (0x1 << 7)
#define FLAG_MASK_TRAP                (0x1 << 8)
#define FLAG_MASK_INTERRUPT_ENABLE    (0x1 << 9)
#define FLAG_MASK_DIRECTION           (0x1 << 10)
#define FLAG_MASK_OVERFLOW            (0x1 << 11)
#define FLAG_MASK_RESERVED12_15       (0xF << 12)

typedef enum reg {
    
} reg_t;

typedef enum gen_idx {
    GEN_IDX_EAX_AX_AL = 0,
    GEN_IDX_ECX_CX_CL = 1,
    GEN_IDX_EDX_DX_DL = 2,
    GEN_IDX_EBX_BX_BL = 3,
    GEN_IDX_ESP_SP_AH = 4,
    GEN_IDX_EBP_BP_CH = 5,
    GEN_IDX_ESI_SI_DH = 6,
    GEN_IDX_EDI_DI_BH = 7,
    GEN_IDX_LAST
} gen_idx_t;

typedef enum reg_seg_idx {
    SEG_IDX_CS,
    SEG_IDX_DS,
    SEG_IDX_ES,
    SEG_IDX_FS,
    SEG_IDX_GS,
    SEG_IDX_LAST
} seg_idx_t;

typedef void (*instr_gen_t)(cpu_t *cpu);

typedef struct reg_file {
    // general purpose registers
    long_t gen[8];
    // segment registers
    word_t seg[REG_SEG_LAST];
    // instruction pointer
    long_t eip;
    // flags
    long_t eflags;
} reg_file_t;

typedef struct instr {
    
} instr_t;

typedef struct cpu {
    bool protected_mode;
    reg_file_t reg_file;
    
    instr_gen_t instr_gen;
} cpu_t;

C86_INLINE void
reg_gen_write_b(reg_file_t *reg_file, reg_gen_idx_t idx, byte_t val) {
    reg_gen_t *reg = cpu->reg_file.gen + (idx & ~0x4);
    idx >= 0x4 ? reg->h8 = val : reg->l8 = val;
}

C86_INLINE byte_t
reg_gen_read_b(reg_file_t *reg_file, reg_gen_idx_t idx) {
    reg_gen_t *reg = reg_file->gen + (idx & ~0x4);
    return idx >= 0x4 ? reg->h8 : reg->l8;
}

C86_INLINE void
reg_gen_write_w(reg_file_t *reg_file, reg_gen_idx_t idx, word_t val) {
    reg_file->gen[idx & ~0x4].l16 = val;
}

C86_INLINE word_t
reg_gen_read_w(reg_file_t *reg_file, reg_gen_idx_t idx) {
    return reg_file->gen[idx & ~0x4].l16;
}

C86_INLINE void
reg_gen_write_l(reg_file_t *reg_file, reg_gen_idx_t idx, long_t val) {
    reg_file->gen[idx & ~0x4].r32 = val;
}

C86_INLINE long_t
reg_gen_read_l(reg_file_t *reg_file, reg_gen_idx_t idx) {
    return reg_file->gen[idx & ~0x4].r32;
}

C86_INLINE void
reg_seg_write(reg_file_t *reg_file, reg_seg_idx_t idx, word_t val) {
    reg_file->seg[idx] = val;
}

C86_INLINE word_t
reg_seg_read(reg_file_t *reg_file, reg_seg_idx_t idx) {
    return reg_file->seg[idx];
}

#endif