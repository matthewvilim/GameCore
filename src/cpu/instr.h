/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/x86_instr.h
 */

#ifndef INSTR
#define INSTR

/* EFLAGS
*
*  31   18  17   16  15   14  13  12  11   10   9    8    7    6   5    4   3    2    1   0
* +-- ~ --+----+----+---+----+------+----+----+----+----+----+----+---+----+---+----+---+----+
* |   -   | VM | RF | 0 | NT | IOPL | OF | DF | IF | TF | SF | ZF | - | AF | - | PF | - | CF |
* +-- ~ --+----+----+---+----+------+----+----+----+----+----+----+---+----+---+----+---+----+
*/
#define X86_EFLAGS_MASK_CF      BIT(0)
#define X86_EFLAGS_MASK_RES0    BIT(1)
#define X86_EFLAGS_MASK_PF      BIT(2)
#define X86_EFLAGS_MASK_RES1    BIT(3)
#define X86_EFLAGS_MASK_AF      BIT(4)
#define X86_EFLAGS_MASK_RES2    BIT(5)
#define X86_EFLAGS_MASK_ZF      BIT(6)
#define X86_EFLAGS_MASK_SF      BIT(7)
#define X86_EFLAGS_MASK_TF      BIT(8)
#define X86_EFLAGS_MASK_IF      BIT(9)
#define X86_EFLAGS_MASK_DF      BIT(10)
#define X86_EFLAGS_MASK_OF      BIT(11)
#define X86_EFLAGS_MASK_IOPL    MASK_RANGE(13, 12)
#define X86_EFLAGS_MASK_NT      BIT(14)
#define X86_EFLAGS_MASK_RES3    BIT(15)
#define X86_EFLAGS_MASK_RF      BIT(16)
#define X86_EFLAGS_MASK_VM      BIT(17)
#define X86_EFLAGS_MASK_RES4    MASK_RANGE(31, 18)

/* ModR/M
 *
 *  7   6 5     3 2     0
 * +-----+-------+-------+
 * | MOD |  Reg  |  R/M  |
 * +-----+-------+-------+
 */
#define X86_MODRM_MOD_MASK    MASK_RANGE(7, 6)
#define X86_MODRM_REG_MASK    MASK_RANGE(5, 3)
#define X86_MODRM_RM_MASK     MASK_RANGE(2, 0)

/* ModR/M
 *
 *  7   6 5     3 2     0
 * +-----+-------+-------+
 * | SS  | Index | Base  |
 * +-----+-------+-------+
 */

#define X86_SIB_SS_MASK       MASK_RANGE(7, 6)
#define X86_SIB_INDEX_MASK    MASK_RANGE(5, 3)
#define X86_SIB_BASE_MASK     MASK_RANGE(2, 0)

// Prefixes
#define X86_PREFIX_REP            0xF3
#define X86_PREFIX_REPE_REPZ      0xF3
#define X86_PREFIX_REPNE_REPNZ    0xF2
#define X86_PREFIX_LOCK           0xF0
#define X86_PREFIX_OVERRIDE_CS    0x2E
#define X86_PREFIX_OVERRIDE_SS    0x36
#define X86_PREFIX_OVERRIDE_DS    0x3E
#define X86_PREFIX_OVERRIDE_ES    0x26

 /* General Registers
  *
  *  31                                   16 15                 8 7                  0
  * +---------------------------------------+--------------------+--------------------+
  * |                                      ExX         xH        xX         xL        |
  * +---------------------------------------+--------------------+--------------------+
  */
#define X86_REG_EAX 0x0
#define X86_REG_ECX 0x1
#define X86_REG_EDX 0x2
#define X86_REG_EBX 0x3
#define X86_REG_ESP 0x4
#define X86_REG_EBP 0x5
#define X86_REG_ESI 0x6
#define X86_REG_EDI 0x7

#define X86_REG_AX 0x0
#define X86_REG_CX 0x1
#define X86_REG_DX 0x2
#define X86_REG_BX 0x3
#define X86_REG_SP 0x4
#define X86_REG_BP 0x5
#define X86_REG_SI 0x6
#define X86_REG_DI 0x7

#define X86_REG_AL 0x0
#define X86_REG_CL 0x1
#define X86_REG_DL 0x2
#define X86_REG_BL 0x3
#define X86_REG_AH 0x4
#define X86_REG_CH 0x5
#define X86_REG_DH 0x6
#define X86_REG_BH 0x7

/* Segment Descriptor (8 bytes)
 *
 *  31         24 23  22  21  20    19          16 15  14 13 12  11   8 7           0
 * +-------------+---+---+---+-----+--------------+---+-----+---+------+-------------+
 * | Base[31:24] | G | D | O | AVL | Limit[19:16] | P | DPL | S | Type | Base[23:16] |
 * +-------------+---+---+---+-----+--------------+---+-----+---+------+-------------+
 *
 *  31                                   16 15                                      0
 * +---------------------------------------+-----------------------------------------+
 * |               Base[15:0]              |              Limit[15:0]                |
 * +---------------------------------------+-----------------------------------------+
 */
#define X86_SEG_DESC_MASK_BASE_23_16    MASK_RANGE(7, 0)
#define X86_SEG_DESC_MASK_TYPE          MASK_RANGE(11, 8)
#define X86_SEG_DESC_MASK_S             BIT(12)
#define X86_SEG_DESC_MASK_DPL           MASK_RANGE(14, 13)
#define X86_SEG_DESC_MASK_P             BIT(15)
#define X86_SEG_DESC_MASK_LIMIT         MASK_RANGE(19, 16)
#define X86_SEG_DESC_MASK_AVL           BIT(20)
#define X86_SEG_DESC_MASK_O             BIT(21)
#define X86_SEG_DESC_MASK_D             BIT(22)
#define X86_SEG_DESC_MASK_G             BIT(23)
#define X86_SEG_DESC_MASK_BASE_31_24    MASK_RANGE(31, 24)
#define X86_SEG_DESC_MASK_LIMIT_15_0    MASK_RANGE(15, 0)
#define X86_SEG_DESC_MASK_BASE_15_0     MASK_RANGE(31, 16)

/* Segment Registers
 *
 *  15                           3  2   1   0
 * +------------------------------+----+-----+
 * |             Index            | TI | RPL | (32 bit address)
 * +------------------------------+----+-----+
 *
 *  15                                       0
 * +-----------------------------------------+
 * |                  Base                   | (16 bit address)
 * +-----------------------------------------+
 */
#define X86_REG_ES 0x0
#define X86_REG_CS 0x1
#define X86_REG_SS 0x2
#define X86_REG_DS 0x3

#define X86_SEG_SELECTOR_MASK_RPL      MASK_RANGE(1, 0)
#define X86_SEG_SELECTOR_MASK_TI       BIT(2)
#define X86_SEG_SELECTOR_MASK_INDEX    MASK_RANGE(15, 3)

typedef uint8_t byte_t;
typedef uint16_t word_t;
typedef uint32_t dword_t;

typedef struct instr {
    byte_t *opcode;

    uint8_t len;

    struct modrm {
        uint8_t reg;
        union {
            uint8_t r;
            struct m {
                uint8_t scale;
                uint8_t index;
                uint8_t base;
                union {
                    int16_t disp16;
                    int32_t disp32;
                };
            };
        };
    };

    byte_t instr_prefix;

    struct flags {
        unsigned int seg_prefix : 1;
        unsigned int op_size : 1;
        unsigned int addr_size;
    }

    instr_calc_addr_t calc_addr;
    instr_exe_t exe;
} instr_t;

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
    calc_addr_t calc_addr;
    uint8_t base;
    uint8_t index;
    uint8_t disp_size;
    bool sib;
} modrm_info_t;

extern op_group_t add;

extern op_info_t add_eb_gb;

extern const op_info_t op_table[];

#endif
