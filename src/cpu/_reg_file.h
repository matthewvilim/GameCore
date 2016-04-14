/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/reg_file_c.h
 */

#ifndef _REG_FILE_H
#define _REG_FILE_H

#include "reg_file.h"

#define REG_GEN_ZERO X86_REG_GEN_COUNT

typedef struct reg_desc_table {
    addr_lin base;
    uword limit;
} reg_desc_table;

typedef struct reg_task {
    uword sel;
    struct cache {
        addr_lin base;
        uword limit;
    };
} reg_task;

typedef struct reg_file {
    udword gen[X86_REG_GEN_COUNT + 1], eip, eflags;

    uword seg[X86_REG_SEG_COUNT];

    udword eip;

    reg_desc_table gdtr, ldtr, idtr;

    reg_task tr;
    uword cr0, cr1, cr2, cr3;

    mmu *mmu;
} reg_file;

C86_INLINE uword_t
reg_file_ip_read(const reg_file *reg_file) {
    return BIT_FIELD_READ(reg_file->eip, MASK_LOW_W);
}

C86_INLINE void
reg_file_ip_write(reg_file *reg_file, uword val) {
    BIT_FIELD_WRITE(reg_file->eip, MASK_LOW_W, val);
}

C86_INLINE uword_t
reg_file_flags_read(const reg_file *reg_file) {
 return BIT_FIELD_READ(reg_file->eflags, MASK_LOW_W);
}

C86_INLINE void
reg_file_flags_write(reg_file *reg_file, uword val) {
    BIT_FIELD_WRITE(reg_file->eflags, MASK_LOW_W, val);
}

C86_INLINE ubyte_t
reg_file_gen_read_b(const reg_file *reg_file, const uint8 reg) {
    udword mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    return BIT_FIELD_READ(reg_file->gen[reg & ~BIT(2)], mask);
}

C86_INLINE uword_t
reg_file_gen_read_w(const reg_file *reg_file, const uint8 reg) {
    return BIT_FIELD_READ(reg_file->gen[reg], MASK_LOW_W);
}

C86_INLINE udword_t
reg_file_gen_read_dw(const reg_file *reg_file, const uint8 reg) {
    return reg_file->gen[reg];
}

C86_INLINE void
reg_file_gen_write_b(reg_file *reg_file, const uint8 reg, ubyte val) {
    udword mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    BIT_FIELD_WRITE(reg_file->gen[reg & ~BIT(2)], mask, val);
}

C86_INLINE void
reg_file_gen_write_w(reg_file *reg_file, const uint8 reg, uword val) {
    BIT_FIELD_WRITE(reg_file->gen[reg], MASK_LOW_W, val);
}

C86_INLINE void
reg_file_gen_write_dw(reg_file *reg_file, const uint8 reg, udword val) {
    reg_file->gen[reg] = val;
}

C86_INLINE uword_t
reg_file_seg_read(reg_file *reg_file, const uint8 reg) {
    return reg_file->seg[reg];
}

C86_INLINE void
reg_file_seg_write(reg_file *reg_file, const uint8 reg, uword val) {
    reg_file->seg[reg] = val;
}

C86_INLINE bool
reg_file_pe_enabled(const reg_file *reg_file) {
    return reg_file->cr0 & X86_CR0_MASK_PE;
}

C86_INLINE bool
reg_file_vm_enabled(const reg_file *reg_file) {
    return reg_file->eflags & X86_EFLAGS_MASK_VM;
}

#endif
