#include "instr.h"

typedef struct op_group {
    char *name;
    uint8_t op1_seg;
    uint8_t op2_seg;
} op_group_t;

typedef struct op_info {
    op_group_t *group;

    decode_t decode_op1;
    decode_t decode_op2;
    instr_exe_t exe;

} op_info_t;

typedef struct modrm_info {
    instr_calc_addr_t calc_addr;
    uint8_t base, index : 3;
    uint8_t disp_size : 2;
    bool sib : 1;
} modrm_info_t;

const op_info_t op_info_table[] = {
    // 0x00
    { .instr_exe = instr_exe_add_Eb_Gb }
}

modrm16_info modrm16_info_table[] {
    // Mod 0x0 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_offset, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = 0 },
    // Mod 0x0 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_offset, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = 0 },
    // Mod 0x0 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_offset, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = 0 },
    // Mod 0x0 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_offset, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = 0 },
    // Mod 0x0 : Reg 0x4 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_offset, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = 0 },
    // Mod 0x0 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_offset, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = 0 },
    // Mod 0x0 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, disp_size = 0 },
    { .calc_addr = calc_addr16_offset, disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, disp_size = 0 },
    // Mod 0x0 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = 0 },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = 0 },
    { .calc_addr = calc_addr16_offset, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = 0 },
    // Mod 0x1 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x1 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x1 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x1 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x1 : eg 0x4 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x1 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x1 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x1 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(ubyte_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(ubyte_t) },
    // Mod 0x2 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x2 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x2 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x2 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x2 : Reg 0x4 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x2 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x2 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x2 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base_index, .base = X86_REG_BX, .index = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_SI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_DI, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base,.base = X86_REG_BP, .disp_size = sizeof(uword_t) },
    { .calc_addr = calc_addr16_base, .base = X86_REG_BX, .disp_size = sizeof(uword_t) },
    // Mod 0x3 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x4 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
}

modrm32_info_t modrm_info_table[] {
    // Mod 0x0 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .disp_size = 0, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x0 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .disp_size = 0, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x0 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .disp_size = 0, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x0 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .disp_size = 0, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x0 : Reg 0x4 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .disp_size = 0, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x0 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .disp_size = 0, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x0 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x0 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base_index, .disp_size = 0, .sib = true },
    { .calc_addr = calc_addr32_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    { .calc_addr = calc_addr32_base, .disp_size = 0, .sib = false },
    // Mod 0x1 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x1 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x1 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x1 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x1 : Reg 0x4 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x1 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x1 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x1 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(ubyte_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(ubyte_t), .sib = false },
    // Mod 0x2 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x2 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x2 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x2 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x2 : Reg 0x4 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x2 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x2 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x2 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_index_offset, .disp_size = sizeof(udword_t), .sib = true },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    { .calc_addr = calc_addr32_base_offset, .disp_size = sizeof(udword_t), .sib = false },
    // Mod 0x3 : Reg 0x0 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x1 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x2 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x3 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x4 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x5 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x6 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    // Mod 0x3 : Reg 0x7 : R/M 0x0-0x7
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
    { .calc_addr = NULL },
}

modrm32_info modrm_info_sib_override = {
    .calc_addr = instr_calc_addr32_index_offset,
    .disp_size = sizeof(udword_t),
    .sib = true
};

INLINE_FORCE void
_decode(instr_t *instr, ubyte_t *buf) {
    instr_t instr;

    for (bool done = false, int i = 0; !done; i++) {
        ubyte_t prefix = buf[i];
        switch (prefix) {
            case X86_PREFIX_REP:
            case X86_PREFIX_REPE_REPZ:
            case X86_PREFIX_REPNE_REPNZ:
            case X86_PREFIX_LOCK:
                instr.instr_prefix = prefix;
                break;
            case X86_PREFIX_OVERRIDE_CS:
                instr.seg_prefix = true;
                instr.seg = seg;
            case X86_PREFIX_OVERRIDE_SS:
                instr.seg_prefix = true;
                instr.seg = seg;
            case X86_PREFIX_OVERRIDE_DS:
                instr.seg_prefix = true;
                instr.seg = seg;
            case X86_PREFIX_OVERRIDE_ES:
                instr.seg_prefix = true;
                instr.seg = seg;
                break;
            default:
                instr.len = i;
                done = true;
                break;
        }
    }

    modrm_info_t *modrm_info;
    uint8_t disp_size;
    if (instr->flags & ADDR16) {
        modrm_info = modrm_info_table16 + modrm;

        instr->addr_calc = modrm_info->calc_addr;
        if (modrm_info->calc_addr) {
            disp_size = modrm_info->disp_size;

            instr->modrm.m.base = modrm_info->base;
            instr->modrm.m.index = modrm_info->index;
        } else {
            instr->modrm.r = BIT_FIELD_READ(modrm, X86_MODRM_RM_MASK);
        }
    } else {
        modrm_info = modrm_info_table32 + modrm;

        instr->addr_calc = modrm_info->calc_addr;
        if (modrm_info->calc_addr) {
            disp_size = modrm_info->disp_size;

            if (modrm_info->sib) {
                instr->modrm.m.base = BIT_FIELD_READ(sib, X86_SIB_BASE_MASK);
                instr->modrm.m.index = BIT_FIELD_READ(sib, X86_SIB_INDEX_MASK);
                instr->modrm.m.scale = BIT_FIELD_READ(sib, X86_SIB_SCALE_MASK);

                if (BIT_FIELD_READ(modrm, X86_MODRM_MOD_MASK) == 0x0 && instr->modrm.m.base == 0x5) {
                    instr->calc_addr = modrm_info_sib_override.calc_addr;
                    disp_size = modrm_info_sib_override.disp_size;
                }
            } else {
                instr->modrm.m.base = BIT_FIELD_READ(modrm, X86_MODRM_RM_MASK);
            }
        } else {
            instr->modrm.r = BIT_FIELD_READ(modrm, X86_MODRM_RM_MASK);
        }

    }
    instr->modrm.reg = BIT_FIELD_READ(modrm, X86_MODRM_REG_MASK);
}
