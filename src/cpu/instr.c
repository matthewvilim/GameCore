#include "instr.h"

typedef struct _op_class {
    char *name;
    uint8_t op1_seg;
    uint8_t op2_seg;
} _op_class_t;

typedef struct _op_info {
    op_class_t *class;
    union {
        struct {
            instr_exe_t *exe;
            bool modrm : 1;
            bool immediate : 1;
        };
        uint8_t group : 3;
    };
} _op_info_t;

typedef enum _disp {
    DISP_NONE,
    DISP_BYTE,
    DISP_WORD,
    DISP_DWORD
} _disp_t;

typedef struct _operand {
    operand_handler_t handler;
    union {
        uint8_t r;
        struct m {
            uint8_t base : 3;
            uint8_t index : 3;
            uint8_t scale : 2;
            enum disp {
                DISP_NONE,
                DISP_BYTE,
                DISP_WORD,
                DISP_DWORD
            } : 2;
        };
    };
    uint8_t reg;
} _operand_t;

typedef struct _sib_info {
    _operand_t operand;
} _sib_info_t;

typedef struct _modrm_info {
    bool sib;
    union {
        _sib_info_t *sib_info;
        _operand_t operand;
    };
} _modrm_info_t;

typedef struct _decode {
    ubyte_t *buf;
    bool seg_override;
    ubyte_t prefix_seg;
    _op_info_t *op_info;
} _decode_t;

const _op_info_t op_table[] = {
    { .class = class_add; .instr_exe = instr_exe_add_Eb_Gb; .modrm = true; },
}

const _op_info_t op_escape_table[] = {
    { .instr_exe = instr_exe_add_Eb_Gb }
}

const _op_info_t op_info_group0[] = {
    { .instr_exe = instr_exe_add_Eb_Gb },
    { .instr_exe = instr_exe_add_Eb_Gb },
    { .instr_exe = instr_exe_add_Eb_Gb },
    { .instr_exe = instr_exe_add_Eb_Gb },
    { .instr_exe = instr_exe_add_Eb_Gb },
    { .instr_exe = instr_exe_add_Eb_Gb },
    { .instr_exe = instr_exe_add_Eb_Gb },
    { .instr_exe = instr_exe_add_Eb_Gb }
}

const _op_info_t op_info_groups[][] = {
    op_info_group0,
    op_info_group1,
    op_info_group2,
    op_info_group3,
    op_info_group4,
    op_info_group5,
    op_info_group6,
    op_info_group7,
}

const _modrm_info_t modrm_info16[] {
    // Mod 0x0 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EAX },
    // Mod 0x0 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ECX },
    // Mod 0x0 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDX },
    // Mod 0x0 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBX },
    // Mod 0x0 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESP },
    // Mod 0x0 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EBP },
    // Mod 0x0 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_ESI },
    // Mod 0x0 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_SI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = X86_REG_DI,   .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_SI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_DI,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX,   .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE, .reg = X86_REG_EDI },
    // Mod 0x1 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    // Mod 0x1 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    // Mod 0x1 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    // Mod 0x1 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    // Mod 0x1 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    // Mod 0x1 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    // Mod 0x1 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    // Mod 0x1 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    // Mod 0x2 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EAX },
    // Mod 0x2 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ECX },
    // Mod 0x2 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDX },
    // Mod 0x2 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    // Mod 0x2 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESP },
    // Mod 0x2 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EBP },
    // Mod 0x2 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_ESI },
    // Mod 0x2 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_SI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = X86_REG_DI,   .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_SI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_DI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_BX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_WORD, .reg = X86_REG_EDI },
    // Mod 0x3 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EAX },
    // Mod 0x3 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_ECX },
    // Mod 0x3 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EDX },
    // Mod 0x3 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EBX },
    // Mod 0x3 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_ESP },
    // Mod 0x3 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EBP },
    // Mod 0x3 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_ESI },
    // Mod 0x3 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EDI }
}

const _modrm_info_t modrm_info32[] {
    // Mod 0x0 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EAX },
    { .sib = true, .table = sib_info0, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EAX },
    // Mod 0x0 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ECX },
    { .sib = true, .table = sib_info0, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ECX },
    // Mod 0x0 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDX },
    { .sib = true, .table = sib_info0, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDX },
    // Mod 0x0 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBX },
    { .sib = true, .table = sib_info0, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBX },
    // Mod 0x0 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESP },
    { .sib = true, .table = sib_info0, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESP },
    // Mod 0x0 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBP },
    { .sib = true, .table = sib_info0, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EBP },
    // Mod 0x0 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESI },
    { .sib = true, .table = sib_info0, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_ESI },
    // Mod 0x0 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDI },
    { .sib = true, .table = sib_info0, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE,  .reg = X86_REG_EDI },
    // Mod 0x1 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = true, .table = sib_info1, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EAX },
    // Mod 0x1 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = true, .table = sib_info1, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ECX },
    // Mod 0x1 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = true, .table = sib_info1, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDX },
    // Mod 0x1 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = true, .table = sib_info1, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBX },
    // Mod 0x1 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = true, .table = sib_info1, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESP },
    // Mod 0x1 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = true, .table = sib_info1, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EBP },
    // Mod 0x1 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = true, .table = sib_info1, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_ESI },
    // Mod 0x1 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = true, .table = sib_info1, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE, .reg = X86_REG_EDI },
    // Mod 0x2 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    { .sib = true, .table = sib_info2, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EAX },
    // Mod 0x2 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    { .sib = true, .table = sib_info2, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ECX },
    // Mod 0x2 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    { .sib = true, .table = sib_info2, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDX },
    // Mod 0x2 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    { .sib = true, .table = sib_info2, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBX },
    // Mod 0x2 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    { .sib = true, .table = sib_info2, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESP },
    // Mod 0x2 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    { .sib = true, .table = sib_info2, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EBP },
    // Mod 0x2 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    { .sib = true, .table = sib_info2, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_ESI },
    // Mod 0x2 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = false, .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    { .sib = true, .table = sib_info2, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    { .sib = false, .rm = false, .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD, .reg = X86_REG_EDI },
    // Mod 0x3 : Reg 0x0 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EAX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EAX },
    // Mod 0x3 : Reg 0x1 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_ECX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_ECX },
    // Mod 0x3 : Reg 0x2 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EDX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EDX },
    // Mod 0x3 : Reg 0x3 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EBX },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EBX },
    // Mod 0x3 : Reg 0x4 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_ESP },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_ESP },
    // Mod 0x3 : Reg 0x5 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EBP },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EBP },
    // Mod 0x3 : Reg 0x6 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_ESI },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_ESI },
    // Mod 0x3 : Reg 0x7 : R/M 0x0-0x7
    { .sib = false, .rm = true, .r = X86_REG_EAX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_ECX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EDX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EBX, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_ESP, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EBP, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_ESI, .reg = X86_REG_EDI },
    { .sib = false, .rm = true, .r = X86_REG_EDI, .reg = X86_REG_EDI }
}

const _sib_info_t sib_info0[] {
    // SS 0x0 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EAX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EAX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EAX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EAX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EAX, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EAX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EAX, .scale = 0, .disp = DISP_NONE },
    // SS 0x0 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ECX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ECX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ECX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ECX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ECX, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ECX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ECX, .scale = 0, .disp = DISP_NONE },
    // SS 0x0 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDX, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDX, .scale = 0, .disp = DISP_NONE },
    // SS 0x0 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBX, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBX, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBX, .scale = 0, .disp = DISP_NONE },
    // SS 0x0 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_NONE },
    // SS 0x0 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBP, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBP, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBP, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBP, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBP, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBP, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBP, .scale = 0, .disp = DISP_NONE },
    // SS 0x0 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ESI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ESI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ESI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ESI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ESI, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ESI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ESI, .scale = 0, .disp = DISP_NONE },
    // SS 0x0 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDI, .scale = 0, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDI, .scale = 0, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDI, .scale = 0, .disp = DISP_NONE },
    // SS 0x1 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EAX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EAX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EAX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EAX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EAX, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EAX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EAX, .scale = 1, .disp = DISP_NONE },
    // SS 0x1 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ECX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ECX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ECX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ECX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ECX, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ECX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ECX, .scale = 1, .disp = DISP_NONE },
    // SS 0x1 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDX, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDX, .scale = 1, .disp = DISP_NONE },
    // SS 0x1 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBX, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBX, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBX, .scale = 1 .disp = DISP_NONE },
    // SS 0x1 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_NONE },
    // SS 0x1 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBP, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBP, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBP, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBP, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBP, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBP, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBP, .scale = 1, .disp = DISP_NONE },
    // SS 0x1 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ESI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ESI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ESI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ESI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ESI, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ESI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ESI, .scale = 1, .disp = DISP_NONE },
    // SS 0x1 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDI, .scale = 1, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDI, .scale = 1, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDI, .scale = 1, .disp = DISP_NONE },
    // SS 0x2 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EAX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EAX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EAX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EAX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EAX, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EAX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EAX, .scale = 2, .disp = DISP_NONE },
    // SS 0x2 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ECX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ECX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ECX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ECX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ECX, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ECX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ECX, .scale = 2, .disp = DISP_NONE },
    // SS 0x2 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDX, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDX, .scale = 2, .disp = DISP_NONE },
    // SS 0x2 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBX, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBX, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBX, .scale = 2, .disp = DISP_NONE },
    // SS 0x2 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_NONE },
    // SS 0x2 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBP, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBP, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBP, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBP, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBP, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBP, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBP, .scale = 2, .disp = DISP_NONE },
    // SS 0x2 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ESI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ESI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ESI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ESI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ESI, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ESI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ESI, .scale = 2, .disp = DISP_NONE },
    // SS 0x2 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDI, .scale = 2, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDI, .scale = 2, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDI, .scale = 2, .disp = DISP_NONE },
    // SS 0x3 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EAX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EAX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EAX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EAX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EAX, .scale = 3, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EAX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EAX, .scale = 3, .disp = DISP_NONE },
    // SS 0x3 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ECX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ECX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ECX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ECX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ECX, .scale = 3, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ECX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ECX, .scale = 3, .disp = DISP_NONE },
    // SS 0x3 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDX, .scale = 3, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDX, .scale = 3, .disp = DISP_NONE },
    // SS 0x3 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBX, .scale = 3 .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBX, .scale = 3 .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBX, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBX, .scale = 3, .disp = DISP_NONE },
    // SS 0x3 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_NONE },
    // SS 0x3 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EBP, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EBP, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EBP, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EBP, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EBP, .scale = 3, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EBP, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EBP, .scale = 3, .disp = DISP_NONE },
    // SS 0x3 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_ESI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_ESI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_ESI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_ESI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_ESI, .scale = 3, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_ESI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_ESI, .scale = 3, .disp = DISP_NONE },
    // SS 0x3 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX,  .index = X86_REG_EDI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ECX,  .index = X86_REG_EDI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDX,  .index = X86_REG_EDI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EBX,  .index = X86_REG_EDI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_ESP,  .index = X86_REG_EDI, .scale = 3, .disp = DISP_NONE },
    { .base = REG_GEN_ZERO, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI,  .index = X86_REG_EDI, .scale = 3, .disp = DISP_NONE },
    { .base = X86_REG_EDI,  .index = X86_REG_EDI, .scale = 3, .disp = DISP_NONE },
}

const _sib_info_t sib_info1[] {
    // SS 0x0 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 0, .disp = DISP_BYTE },
    // SS 0x0 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 0, .disp = DISP_BYTE },
    // SS 0x0 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 0, .disp = DISP_BYTE },
    // SS 0x0 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 0, .disp = DISP_BYTE },
    // SS 0x0 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_BYTE },
    // SS 0x0 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 0, .disp = DISP_BYTE },
    // SS 0x0 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 0, .disp = DISP_BYTE },
    // SS 0x0 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 0, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 1, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 1, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 1, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 1, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 1, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 1, .disp = DISP_BYTE },
    // SS 0x1 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 1, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 2, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 2, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 2, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 2, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 2, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 2, .disp = DISP_BYTE },
    // SS 0x2 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 2, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 3, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 3, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 3, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 3, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 3, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 3, .disp = DISP_BYTE },
    // SS 0x3 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 3, .disp = DISP_BYTE }
}

const _sib_info_t sib_info2[] {
    // SS 0x0 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 0, .disp = DISP_DWORD },
    // SS 0x0 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 0, .disp = DISP_DWORD },
    // SS 0x0 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 0, .disp = DISP_DWORD },
    // SS 0x0 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 0, .disp = DISP_DWORD },
    // SS 0x0 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 0, .disp = DISP_DWORD },
    // SS 0x0 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 0, .disp = DISP_DWORD },
    // SS 0x0 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 0, .disp = DISP_DWORD },
    // SS 0x0 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 0, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 1, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 1, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 1, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 1, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 1, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 1, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 1, .disp = DISP_DWORD },
    // SS 0x1 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 1, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 2, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 2, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 2, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 2, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 2, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 2, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 2, .disp = DISP_DWORD },
    // SS 0x2 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 2, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x0 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EAX, .scale = 3, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x1 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ECX, .scale = 3, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x2 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDX, .scale = 3, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x3 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBX, .scale = 3, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x4 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = REG_GEN_ZERO, .scale = 3, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x5 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EBP, .scale = 3, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x6 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_ESI, .scale = 3, .disp = DISP_DWORD },
    // SS 0x3 : Index 0x7 : Base 0x0-0x7
    { .base = X86_REG_EAX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ECX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBX, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESP, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EBP, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_ESI, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD },
    { .base = X86_REG_EDI, .index = X86_REG_EDI, .scale = 3, .disp = DISP_DWORD }
}

static INLINE_FORCE void
_decode_prefix(instr_t *instr, _decode_t *decode) {
    bool decode->seg_override = false;
    for (ubyte_t prefix = mem_host_read_b(decode->buf); true; decode->buf++, instr->len++)
        switch (prefix) {
            case X86_PREFIX_REP:
            case X86_PREFIX_REPE_REPZ:
            case X86_PREFIX_REPNE_REPNZ:
            case X86_PREFIX_LOCK:
                instr_prefix = prefix;
                break;
            case X86_PREFIX_OVERRIDE_CS:
                decode->seg_override = true;
                decode->prefix_seg = X86_REG_CS;
                break;
            case X86_PREFIX_OVERRIDE_SS:
                decode->seg_override = true;
                decode->prefix_seg = X86_REG_SS;
                break;
            case X86_PREFIX_OVERRIDE_DS:
                decode->seg_override = true;
                decode->prefix_seg = X86_REG_DS;
                break;
            case X86_PREFIX_OVERRIDE_ES:
                decode->seg_override = true;
                decode->prefix_seg = X86_REG_ES;
                break;
            default: return;
        }
    }
}

static INLINE_FORCE void
_decode_opcode(instr_t *instr, _decode_t *decode) {
    ubyte_t opcode = mem_host_read_b(decode->buf++);

    for (ubyte_t opcode = mem_host_read_b(decode->buf), _op_info_t *table = op_table; true; decode->buf++) {
        switch (opcode) {
            case X86_TWO_BYTE_OPCODE_ESCAPE:
                table = op_table_escape;
                instr->len++;
                continue;
            default:
                decode->op_info = table[opcode];
                instr->len++;
                goto done;
        }
    }

done:
    if (op_info->group) {
        ubyte_t modrm
    }
}

INLINE_FORCE void
instr_init(instr_t *instr, ubyte_t *buf) {
    ASSERT(instr && buf);

    instr->calc_addr = NULL;
    instr->len = 0;

    _decode_context_t decode = { .buf = buf };

    _decode_prefix(instr, &decode);
    _decode_opcode(instr, &decode);



    if (op_info->modrm) {
        ubyte_t modrm = mem_host_read_b(buf++);
        instr->len++;

        modrm_info_t *modrm_info;
        uint8_t disp_size = 0;
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
                    ubyte_t sib = mem_host_read_b(buf++);
                    instr->len++;

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
        uint8_t reg = BIT_FIELD_READ(modrm, X86_MODRM_REG_MASK);
        instr->modrm.reg = reg;
        if (!op_info->class) {
            op_info = op_info_groups[op_info->group][reg];
        }

        switch (disp_size) {
            case 0: break;
            case sizeof(ubyte_t):
                instr->disp32 = mem_host_read_b(buf);
            case sizeof(uword_t):
                instr->disp32 = mem_host_read_w(buf);
            case sizeof(udword_t):
                instr->disp32 = mem_host_read_dw(buf);
            default: break;
        }
        buf += disp_size;
        instr->len += disp_size;
    }

}
