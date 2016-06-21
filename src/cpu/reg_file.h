/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/reg_file.h
 */

#ifndef REG_FILE_H
#define REG_FILE_H

typedef reg_file reg_file;

enum reg_file_gen_dw {
    REG_FILE_GEN_EAX,
    REG_FILE_GEN_EBX,
    REG_FILE_GEN_ECX,
    REG_FILE_GEN_EDX,
    REG_FILE_GEN_EBP,
    REG_FILE_GEN_ESP,
    REG_FILE_GEN_ESI,
    REG_FILE_GEN_EDI,
    REG_FILE_GEN_COUNT
};

enum reg_file_gen_w {
    REG_FILE_GEN_AX,
    REG_FILE_GEN_BX,
    REG_FILE_GEN_CX,
    REG_FILE_GEN_DX,
    REG_FILE_GEN_BP,
    REG_FILE_GEN_SP,
    REG_FILE_GEN_SI,
    REG_FILE_GEN_DI
};

enum reg_file_gen_b {
    REG_FILE_GEN_AL,
    REG_FILE_GEN_BL,
    REG_FILE_GEN_CL,
    REG_FILE_GEN_DL,
    REG_FILE_GEN_AH,
    REG_FILE_GEN_BH,
    REG_FILE_GEN_CH,
    REG_FILE_GEN_DH
};

enum reg_file_seg {
    REG_FILE_SEG_CS,
    REG_FILE_SEG_DS,
    REG_FILE_SEG_ES,
    REG_FILE_SEG_SS,
    REG_FILE_SEG_FS,
    REG_FILE_SEG_GS,
    REG_FILE_SEG_COUNT
};

enum reg_file_cr {
    REG_FILE_CR0,
    REG_FILE_CR1,
    REG_FILE_CR2,
    REG_FILE_CR3
};

enum reg_file_desc_table {
    REG_DESC_TABLE_GLOBAL,
    REG_DESC_TABLE_LOCAL,
    REG_DESC_TABLE_INTERRUPT
};

struct reg_desc_table {
    addr_lin base;
    uword limit;
};

struct reg_file {
    dword gen[REG_FILE_GEN_COUNT], eip, eflags;

    word seg[REG_FILE_SEG_COUNT];

    dword eip;

    reg_desc_table gdtr, ldtr, idtr;

    reg_task tr;
    uword cr0, cr1, cr2, cr3;
};

void reg_file_init(reg_file *reg_file);
void reg_file_reset(reg_file *reg_file);

#endif
