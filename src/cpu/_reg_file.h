/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/reg_file_c.h
 */

#ifndef _REG_FILE_H
#define _REG_FILE_H

#include "reg_file.h"

typedef enum reg_file_gen {
    REG_FILE_GEN_EAX,
    REG_FILE_GEN_EBX,
    REG_FILE_GEN_ECX,
    REG_FILE_GEN_EDX,
    REG_FILE_GEN_ESP,
    REG_FILE_GEN_EBP,
    REG_FILE_GEN_ESI,
    REG_FILE_GEN_EDI,

    REG_FILE_GEN_AX,
    REG_FILE_GEN_BX,
    REG_FILE_GEN_CX,
    REG_FILE_GEN_DX,
    REG_FILE_GEN_BP,
    REG_FILE_GEN_SP,
    REG_FILE_GEN_SI,
    REG_FILE_GEN_DI,

    REG_FILE_GEN_AL,
    REG_FILE_GEN_AH,
    REG_FILE_GEN_BL,
    REG_FILE_GEN_BH,
    REG_FILE_GEN_CL,
    REG_FILE_GEN_CH,
    REG_FILE_GEN_DL,
    REG_FILE_GEN_DH
} reg_file_gen;

typedef enum reg_file_seg {
    REG_FILE_SEG_CS,
    REG_FILE_SEG_DS,
    REG_FILE_SEG_ES,
    REG_FILE_SEG_SS,
    REG_FILE_SEG_FS,
    REG_FILE_SEG_GS
} reg_file_seg;

typedef enum reg_file_cr {
    REG_FILE_CR0,
    REG_FILE_CR1,
    REG_FILE_CR2,
    REG_FILE_CR3
} reg_file_cr;

typedef enum reg_file_desc_table {
    REG_DESC_TABLE_GLOBAL,
    REG_DESC_TABLE_LOCAL,
    REG_DESC_TABLE_INTERRUPT
} reg_desc_table;

typedef struct reg_desc_table {
    addr_lin base;
    uword limit;
} reg_desc_table;

struct reg_file {
    udword eax, ebx, ecx, edx, esp, edi, esp, ebp, eip, eflags;

    uword fs, gs, cs, ss, ds, es;

    udword eip;

    reg_desc_table gdtr, ldtr, idtr;

    reg_task tr;
    uword cr0, cr1, cr2, cr3;
};

C86_INLINE ubyte_t
reg_file_read_gen_b(const reg_file *rf, const reg r) {
    switch (r) {
        case REG_AL: return BIT_FIELD_READ(rf->eax, MASK_LOW_B);
        case REG_AH: return BIT_FIELD_READ(rf->eax, MASK_HIGH_B);
        case REG_BL: return BIT_FIELD_READ(rf->ebx, MASK_LOW_B);
        case REG_BH: return BIT_FIELD_READ(rf->ebx, MASK_HIGH_B);
        case REG_CL: return BIT_FIELD_READ(rf->ecx, MASK_LOW_B);
        case REG_CH: return BIT_FIELD_READ(rf->ecx, MASK_HIGH_B);
        case REG_DL: return BIT_FIELD_READ(rf->edx, MASK_LOW_B);
        case REG_DH: return BIT_FIELD_READ(rf->edx, MASK_HIGH_B);
        case REG_ZERO: return 0;
    }
}

C86_INLINE void
reg_file_write_gen_b(reg_file *rf, const reg r, const val) {
    switch (r) {
        case REG_GEN_AL: BIT_FIELD_WRITE(rf->eax, MASK_LOW_B, val);
        case REG_GEN_AH: BIT_FIELD_WRITE(rf->eax, MASK_HIGH_B, val);
        case REG_GEN_BL: BIT_FIELD_WRITE(rf->ebx, MASK_LOW_B, val);
        case REG_GEN_BH: BIT_FIELD_WRITE(rf->ebx, MASK_HIGH_B, val);
        case REG_GEN_CL: BIT_FIELD_WRITE(rf->ecx, MASK_LOW_B, val);
        case REG_GEN_CH: BIT_FIELD_WRITE(rf->ecx, MASK_HIGH_B, val);
        case REG_GEN_DL: BIT_FIELD_WRITE(rf->edx, MASK_LOW_B, val);
        case REG_GEN_DH: BIT_FIELD_WRITE(rf->edx, MASK_HIGH_B, val);
        default: // throw
    }
}

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
