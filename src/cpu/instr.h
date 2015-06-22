/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/x86_instr.h
 */

#ifndef INSTR
#define INSTR

/******************
 * REGISTER MASKS *
 ******************/

#define X86_FLAG_MASK_CF      BIT(0)
#define X86_FLAG_MASK_RES0    BIT(1)
#define X86_FLAG_MASK_PF      BIT(2)
#define X86_FLAG_MASK_RES1    BIT(3)
#define X86_FLAG_MASK_AF      BIT(4)
#define X86_FLAG_MASK_RES2    BIT(5)
#define X86_FLAG_MASK_ZF      BIT(6)
#define X86_FLAG_MASK_SF      BIT(7)
#define X86_FLAG_MASK_TF      BIT(8)
#define X86_FLAG_MASK_IF      BIT(9)
#define X86_FLAG_MASK_DF      BIT(10)
#define X86_FLAG_MASK_OF      BIT(11)
#define X86_FLAG_MASK_RES3    MASK_RANGE(15, 12)

/*********************
 * INSTRUCTION MASKS *
 *********************/

#define X86_MODRM_MOD_MASK     MASK_RANGE(7, 6)
#define X86_MODRM_REG_MASK     MASK_RANGE(5, 3)
#define X86_MODRM_RM_MASK      MASK_RANGE(2, 0)

/************
 * PREFIXES *
 ************/
#define X86_PREFIX_REP            0xF3
#define X86_PREFIX_REPE_REPZ      0xF3
#define X86_PREFIX_REPNE_REPNZ    0xF2
#define X86_PREFIX_LOCK           0xF0
#define X86_PREFIX_OVERRIDE_CS    0x2E
#define X86_PREFIX_OVERRIDE_SS    0x36
#define X86_PREFIX_OVERRIDE_DS    0x3E
#define X86_PREFIX_OVERRIDE_ES    0x26

/****************************
 * INSTRUCTION FIELD VALUES *
 ****************************/
// general registers (16 bit)
#define X86_REG_AX 0x0
#define X86_REG_CX 0x1
#define X86_REG_DX 0x2
#define X86_REG_BX 0x3
#define X86_REG_SP 0x4
#define X86_REG_BP 0x5
#define X86_REG_SI 0x6
#define X86_REG_DI 0x7
// general registers (8 bit)
#define X86_REG_AL 0x0
#define X86_REG_CL 0x1
#define X86_REG_DL 0x2
#define X86_REG_BL 0x3
#define X86_REG_AH 0x4
#define X86_REG_CH 0x5
#define X86_REG_DH 0x6
#define X86_REG_BH 0x7
// segment registers
#define X86_REG_ES 0x0
#define X86_REG_CS 0x1
#define X86_REG_SS 0x2
#define X86_REG_DS 0x3

// MOD - Mode
#define X86_MOD_NO_DISP    0x0
#define X86_MOD_B_DISP     0x1
#define X86_MOD_W_DISP     0x2
#define X86_MOD_REG        0x3
// R/M - Register/Memory
// MOD = 0x0, 0x1, 0x2
#define X86_INSTR_RM_BX_PLUS_SI    0x0
#define X86_INSTR_RM_BX_PLUS_DI    0x1
#define INSTR_RM_BP_PLUS_SI        0x2
#define INSTR_RM_BP_PLUS_DI        0x3
#define INSTR_RM_SI                0x4
#define INSTR_RM_DI                0x5
#define INSTR_RM_BP_OR_DIR_ADDR    0x6
#define INSTR_RM_BX                0x7
// MOD = 0x3
#define INSTR_RM_AL_AX    0x0
#define INSTR_RM_CL_CX    0x1
#define INSTR_RM_DL_DX    0x2
#define INSTR_RM_BL_BX    0x3
#define INSTR_RM_AH_SP    0x4
#define INSTR_RM_CH_BP    0x5
#define INSTR_RM_DH_SI    0x6
#define INSTR_RM_BH_DI    0x7

#define INSTR_FLAGS_SEG_PREFIX     BIT(0)
#define INSTR_FLAGS_OP_SIZE_MASK   BIT(1)
#define INSTR_FLAGS_ADDR_SIZE_MASK BIT(2)

typedef uint8_t byte_t;
typedef uint16_t word_t;
typedef uint32_t dword_t;

typedef struct operand {
    addr_calc_t addr_calc;
    uint8_t seg;
    union {

    }
    union {
        byte_t *b;
        word_t *w;
        dword_t *dw;
    };
} operand_t;

typedef struct modrm {
    uint8_t scale;
    union {
        uint8_t index;
    }
    union {
        uint8_t base;
    }
    union {
        int16_t disp16;
        int32_t disp32;
    };
} modrm_t;

typedef struct instr {
    byte_t *opcode;

    uint8_t len;

    modrm_t modrm;
    size_t modrm_len;

    byte_t instr_prefix;

    uint8_t flags;

    operand_t op1, op2;
    instr_exe_t exe;
} instr_t;


typedef void (*instr_exe_t)(cpu_t *cpu, instr_t *instr);

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

extern op_group_t add;

extern op_info_t add_eb_gb;

extern const op_info_t op_table[];

#endif
