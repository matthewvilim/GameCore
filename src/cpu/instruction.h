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

/*********************
 * INSTRUCTION MASKS *
 *********************/

#define INSTR_B1_W_0_MASK        MASK_RANGE(0, 0)
#define INSTR_B1_W_3_MASK        MASK_RANGE(3, 3)
#define INSTR_B1_D_MASK          MASK_RANGE(1, 1)
#define INSTR_B1_REG_2_0_MASK    MASK_RANGE(2, 0)
#define INSTR_B1_S_MASK          MASK_RANGE(1, 1)
#define INSTR_B2_MOD_7_6_MASK    MASK_RANGE(7, 6)
#define INSTR_B2_REG_5_3_MASK    MASK_RANGE(5, 3)
#define INSTR_B2_RM_2_0_MASK     MASK_RANGE(2, 0)
#define INSTR_B2_SR_3_2_MASK     MASK_RANGE(3, 2)

/****************************
 * INSTRUCTION FIELD VALUES *
 ****************************/

// REG - Register
#define INSTR_REG_AX_AL    0x0
#define INSTR_REG_CX_CL    0x1
#define INSTR_REG_DX_DL    0x2
#define INSTR_REG_BX_BL    0x3
#define INSTR_REG_AH_SP    0x4
#define INSTR_REG_CH_BP    0x5
#define INSTR_REG_DH_SI    0x6
#define INSTR_REG_BH_DI    0x7
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

typedef enum {
    SEGMENT_CODE,
    SEGMENT_DATA,
    SEGMENT_EXTRA,
    SEGMENT_STACK,
} segment_t;

typedef enum {
    // data transfer
    OPCODE_ADD_REG_MEM,
    OPCODE_ADD_IMM_TO_REG_MEM,
    OPCODE_ADD_IMM_TO_ACCUM,
} opcode_t;

typedef struct op_info {
    opcode_t opcode;
    uint8_t size_min;
    uint8_t d_mask, w_mask, mod_mask, reg_mask, rm_mask, sr_mask;
    uint8_t *instr;
    bool dynarec_support;
} op_info_t;

typedef instr {
    op_info_t *op_info;
    segment_t segment_override;
    bool d, w;
    uint8_t mod, reg, sr, rm;
    uint8_t size;
} instr_t;

/********************************
 * INSTRUCTIONS - DATA TRANSFER *
 ********************************/

/*
 * MOV - Move
 *
 * Register/memory to/from register
 *   7   6   5   4   3   2   1   0     7   6   5       3   2       0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 0 | 0 | 1 | 0 | d | w | |  mod  |    reg    |    r/m    | |           (DISP-LO)           | |           (DISP-HI)           |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3                                B4
 *
 * Immediate to register/memory
 *   7   6   5   4   3   2   1   0     7   6   5   4   3   2       0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 1 | 0 | 0 | 0 | 1 | 1 | w | |  mod  | 0 | 0 | 0 |    r/m    | |           (DISP-LO)           | |           (DISP-HI)           | cont.
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3                                B4
 *   7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * |             data              | |         data if w = 1         |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B5                                B6
 *
 * Immediate to register
 *   7   6   5   4   3   2       0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 1 | 1 | w |    reg    | |             data              | |         data if w = 1         |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3
 *
 * Memory to accumulator
 *   7   6   5   4   3   2   1   0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 1 | 0 | 0 | 0 | 0 | w | |            addr-lo            | |            addr-hi            |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3
 *
 * Accumulator to memory
 *   7   6   5   4   3   2   1   0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 1 | 0 | 0 | 0 | 1 | w | |            addr-lo            | |            addr-hi            |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3
 *
 * Register/memory to segment register
 *   7   6   5   4   3   2   1   0     7   6   5   4   3   2       0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | |  mod  | 0 |   SR  |    r/m    | |           (DISP-LO)           | |           (DISP-HI)           |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3                                B4
 *
 * Segment register to register/memory
 *   7   6   5   4   3   2   1   0     7       5   4   3   2       0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | |  mod  | 0 |   SR  |    r/m    | |           (DISP-LO)           | |           (DISP-HI)           |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3                                B4
 */

static const op_info_t mov_reg_mem_to_from_reg = {
    .opcode = OPCODE_ADD_REG_MEM,
    .size_min = 3,
    .mod_mask = INSTR_B2_MOD_7_6_MASK,
    .reg_mask = INSTR_B2_REG_5_3_MASK,
    .rm_mask = INSTR_B2_RM_2_0_MASK
}

/*****************************
 * INSTRUCTIONS - ARITHMETIC *
 *****************************/

/*
 * ADD - Add
 *
 * Register/memory with register to either
 *   7   6   5   4   3   2   1   0     7   6   5       3   2       0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | d | w | |  mod  |    reg    |    r/m    | |           (DISP-LO)           | |           (DISP-HI)           |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3                                B4
 *
 * Immediate to register/memory
 *   7   6   5   4   3   2   1   0     7   6   5   4   3   2       0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 0 | 0 | 0 | 0 | s | w | |  mod  | 0 | 0 | 0 |    r/m    | |           (DISP-LO)           | |           (DISP-HI)           | cont.
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3                                B4
 *   7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * |             data              | |         data if w = 1         |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B5                                B6
 *
 * Immediate to accumulator
 *   7   6   5   4   3   2   1   0     7                           0     7                           0
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 1 | 0 | w | |             data              | |         data if w = 1         |
 * +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+ +---+---+---+---+---+---+---+---+
 *                 B1                                B2                                B3
 *
 */

static const op_info_t add_reg_mem_with_reg_to_either = { .opcode = OPCODE_ADD_REG_MEM, .size = 3, .mod_mask = INSTR_B2_MOD_7_6_MASK,
                                                          .reg_mask = INSTR_B2_REG_5_3_MASK, .rm_mask = INSTR_B2_RM_2_0_MASK }

static const op_info_t op_table[] = {
    add_reg_mem_with_reg_to_either, // 0x00
    add_reg_mem_with_reg_to_either, // 0x01
    add_reg_mem_with_reg_to_either, // 0x10
    add_reg_mem_with_reg_to_either, // 0x11
    
}

#endif