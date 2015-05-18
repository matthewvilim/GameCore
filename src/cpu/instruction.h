/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

/******************
 * REGISTER MASKS *
 ******************/

#define EFLAG_MASK_CF      BIT(0)
#define EFLAG_MASK_RES0    BIT(1)
#define EFLAG_MASK_PF      BIT(2)
#define EFLAG_MASK_RES1    BIT(3)
#define EFLAG_MASK_AF      BIT(4)
#define EFLAG_MASK_RES2    BIT(5)
#define EFLAG_MASK_ZF      BIT(6)
#define EFLAG_MASK_SF      BIT(7)
#define EFLAG_MASK_TF      BIT(8)
#define EFLAG_MASK_IF      BIT(9)
#define EFLAG_MASK_DF      BIT(10)
#define EEFLAG_MASK_OF     BIT(11)
#define EFLAG_MASK_IOPL    MASK_RANGE(13, 12)
#define EFLAG_MASK_NT      BIT(14)
#define EFLAG_MASK_RES3    BIT(15)
#define EFLAG_MASK_RF      BIT(16)
#define EFLAG_MASK_VM      BIT(17)
#define EFLAG_MASK_AC      BIT(18)
#define EFLAG_MASK_RES4    MASK_RANGE(31, 19)

/*********************
 * INSTRUCTION MASKS *
 *********************/

#define INSTR_OPCODE_W_0_MASK    BIT(0)
#define INSTR_OPCODE_W_3_MASK    BIT(3)
#define INSTR_OPCODE_D_MASK      BIT(1)
#define INSTR_OPCODE_REG_MASK    MASK_RANGE(2, 0)
#define INSTR_OPCODE_S_MASK      BIT(1)
#define INSTR_MODRM_MOD_MASK     MASK_RANGE(7, 6)
#define INSTR_MODRM_REG_MASK     MASK_RANGE(5, 3)
#define INSTR_MODRM_RM_MASK      MASK_RANGE(2, 0)

/****************************
 * INSTRUCTION FIELD VALUES *
 ****************************/
// 32 bit registers
#define INSTR_REG_EAX 0x0
#define INSTR_REG_ECX 0x1
#define INSTR_REG_EDX 0x2
#define INSTR_REG_EBX 0x3
#define INSTR_REG_ESP 0x4
#define INSTR_REG_EBP 0x5
#define INSTR_REG_ESI 0x6
#define INSTR_REG_EDI 0x7
// 16 bit registers
#define INSTR_REG_AX 0x0
#define INSTR_REG_CX 0x1
#define INSTR_REG_DX 0x2
#define INSTR_REG_BX 0x3
#define INSTR_REG_SP 0x4
#define INSTR_REG_BP 0x5
#define INSTR_REG_SI 0x6
#define INSTR_REG_DI 0x7
// 8 bit registers
#define INSTR_REG_AL 0x0
#define INSTR_REG_CL 0x1
#define INSTR_REG_DL 0x2
#define INSTR_REG_BL 0x3
#define INSTR_REG_AH 0x4
#define INSTR_REG_CH 0x5
#define INSTR_REG_DH 0x6
#define INSTR_REG_BH 0x7

// MOD - Mode
#define INSTR_MOD_NO_DISP    0x0
#define INSTR_MOD_B_DISP     0x1
#define INSTR_MOD_W_DISP     0x2
#define INSTR_MOD_REG        0x3
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

/************************
 * INSTRUCTION PREFIXES *
 ************************/

 typedef enum prefix_instr {
    PREFIX_REP,
    PREFIX_REPE_REPZ,
    PREFIX_REPNE_REPNZ,
    PREFIX_LOCK
} prefix_t;

typedef enum prefix_seg {
    PREFIX_SEG_CS,
    PREFIX_SEG_SS,
    PREFIX_SEG_DS,
    PREFIX_SEG_ES,
    PREFIX_SEG_FS,
    PREFIX_SEG_GS
} prefix_seg_t;

typedef enum {
    ADDRESSING_A = 1 << 0,
    ADDRESSING_C = 1 << 1,
    ADDRESSING_D = 1 << 2,
    ADDRESSING_E = 1 << 3,
    ADDRESSING_F = 1 << 4,
    ADDRESSING_G = 1 << 5,
    ADDRESSING_I = 1 << 6,
    ADDRESSING_J = 1 << 7,
    ADDRESSING_M = 1 << 8,
    ADDRESSING_O = 1 << 9,
    ADDRESSING_R = 1 << 10,
    ADDRESSING_S = 1 << 11,
    ADDRESSING_T = 1 << 12,
    ADDRESSING_X = 1 << 13,
    ADDRESSING_Y = 1 << 14,
} addressing_t;

typedef enum {
    OPERANT_A = 1 << 0,
    OPERANT_B = 1 << 1,
    OPERANT_C = 1 << 2,
    OPERANT_D = 1 << 3,
    OPERANT_P = 1 << 4,
    OPERANT_S = 1 << 5,
    OPERANT_V = 1 << 6,
    OPERANT_W = 1 << 7
} operant_t;

typedef struct op_group {
    char *name;
} op_group_t;

typedef struct op_info {
    opcode_group_t group;
    addressing_t addressing;
    operant_t operant;
    bool dynarec;
} op_info_t;

typedef enum operand_type {
    OPERAND_REG,
    OPERAND_ADDR
} operand_type_t;

typedef enum dir {
    DIR_REG_TO_RM,
    DIR_RM_TO_REG
} dir_t;

typedef struct {
    operand_type_t type;
    union {
        const reg_gen_t *reg;
        dword_t addr;
    };
} operand_t;

extern const reg_gen_idx modrm_byte[];
extern const reg_gen_idx modrm_word[];
extern const reg_gen_idx modrm_dword[];

#endif
