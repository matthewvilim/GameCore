/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

/******************
 * REGISTER MASKS *
 ******************/

#define FLAG_MASK_CF      BIT(0)
#define FLAG_MASK_RES0    BIT(1)
#define FLAG_MASK_PF      BIT(2)
#define FLAG_MASK_RES1    BIT(3)
#define FLAG_MASK_AF      BIT(4)
#define FLAG_MASK_RES2    BIT(5)
#define FLAG_MASK_ZF      BIT(6)
#define FLAG_MASK_SF      BIT(7)
#define FLAG_MASK_TF      BIT(8)
#define FLAG_MASK_IF      BIT(9)
#define FLAG_MASK_DF      BIT(10)
#define FLAG_MASK_OF      BIT(11)
#define FLAG_MASK_RES3    MASK_RANGE(15, 12)

/*********************
 * INSTRUCTION MASKS *
 *********************/

#define X86_OPCODE_W_0_MASK    BIT(0)
#define X86_OPCODE_W_3_MASK    BIT(3)
#define X86_OPCODE_D_MASK      BIT(1)
#define X86_OPCODE_REG_MASK    MASK_RANGE(2, 0)
#define X86_OPCODE_S_MASK      BIT(1)
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
#define INSTR_RM_BX+SI             0x0
#define INSTR_RM_BX+DI             0x1
#define INSTR_RM_BP+SI             0x2
#define INSTR_RM_BP+DI             0x3
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

typedef enum {
    AddressingCodeNone,
    AddressingCodeA,
    AddressingCodeE,
    AddressingCodeG,
    AddressingCodeI,
    AddressingCodeJ,
    AddressingCodeM,
    AddressingCodeO,
    AddressingCodeS
} addressing_code_t;

typedef enum {
    OperandCode0,
    OperandCodeB,
    OperandCodeP,
    OperandCodeW,
    OperandCodeV
} operand_code_t;

typedef enum register_code {
    RegisterCodeNone,
    RegisterCodeAL,
    RegisterCodeCL,
    RegisterCodeDL,
    RegisterCodeBL,
    RegisterCodeAH,
    RegisterCodeCH,
    RegisterCodeDH,
    RegisterCodeBH,
    RegisterCodeAX,
    RegisterCodeCX,
    RegisterCodeDX,
    RegisterCodeBX,
    RegisterCodeSP,
    RegisterCodeBP,
    RegisterCodeSI,
    RegisterCodeDI,
    RegisterCodeES,
    RegisterCodeCS,
    RegisterCodeSS,
    RegisterCodeDS
} register_code_t;

typedef struct op_group {
    char *name;
} op_group_t;

typedef struct op_info {
    op_group_t *group;
    addressing_code_t src;
    addressing_code_t dst;
    operand_code_t  operand_code;
    register_code_t register_code;
} op_info_t;

extern op_group_t add;

extern op_info_t add_eb_gb;

extern const op_info_t op_table[];

#endif
