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

#define REG_EAX 0
#define REG_

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

typedef struct opcode {
    char *name;
    addressing_t addressing;
    operant_t operant;
    uint8_t size;
    bool dynarec;
} opcode_t;

/**************
 * OPCODE MAP *
 **************/

/*                                   One-byte Opcode Map (0x00 - 0xF7)
 *         0          1          2          3          4          5          6          7
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               ADD                               |          |          |
 * 0 +          +          +          +          +          +          + PUSH ES  +  POP ES  +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               ADC                               |          |          |
 * 1 +          +          +          +          +          +          +  PUSH SS +  POP SS  +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               AND                               |          |          |
 * 2 +          +          +          +          +          +          + SEG = ES +   DAA    +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  | (Prefix) |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               XOR                               |          |          |
 * 3 +          +          +          +          +          +          + SEG = SS +   AAA    +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  | (Prefix) |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                                 INC general register                                  |
 * 4 +          +          +          +          +          +          +          +          +
 *   |    eAX   |    eCX   |   eDX    |    eBX   |    eSP   |   eBP    |    eSI   |   eDI    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                                 PUSH general register                                 |
 * 5 +          +          +          +          +          +          +          +          +
 *   |    eAX   |    eCX   |   eDX    |    eBX   |    eSP   |   eBP    |    eSI   |   eDI    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |  PUSHA/  |   POPA/  |   BOUND  |   ARPL   |          |          |  Operand |  Address |
 * 6 +  PUSHAD  +   POPAD  +          +          + SE G= FS + SEG = GS +   Size   +   Size   +
 *   |          |          |  Gv, Ma  |  Ew, Gw  | (Prefix) | (Prefix) | (Prefix) | (Prefix) |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                      Jcc  - Short-displacement jump on condition                      |
 * 7 +     O    +    NO    +  B/NAE/C + NB/AE/NC +    Z/E   +   NZ/NE  +   BE/NA  +   NBE/A  +
 *   |    Jb    |    Jb    |    Jb    |    Jb    |    Jb    |    Jb    |    Jb    |    Jb    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |              Immediate Grp 1              |         TEST        |         XCHG        |
 * 8 +          +          +          +          +          +          +          +          +
 *   |  Eb, Ib  |  Ev, Iz  |  Eb, Ib  |  Ev, Ib  |  Eb, Gb  |  Ev, Gv  |  Eb, Gb  |  Ev, Gv  |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |          |                  XCHG word, double-word register with eAX                  |
 * 9 +    NOP   +          +          +          +          +          +          +          +
 *   |          |    eCX   |    eDX   |    eBX   |    eSP   |    eBP   |    eSI   |    eDI   |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                    MOV                    |  MOVS/B  | MOVS/W/D |  CMPS/B  | CMPS/W/D |
 * A +          +          +          +          +          +          +          +          +
 *   |  AL, Ob  |  eAX, Ov |  Ob, AL  |  Ov, eAX |  Yb, Xb  |  Yv, Xv  |  Xb, Yb  |  Xv, Yv  |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                         MOV immediate byte into byte register                         |
 * B +          +          +          +          +          +          +          +          +
 *   |    AL    |    CL    |    DL    |    BL    |    AH    |    CH    |    DH    |    BH    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |     Shift Grp 2     |       near RET      |    LES   |    LDS   |     Grp 11 - MOV    |
 * C +          +          +          +          +          +          +          +          +
 *   |          |          |    Iw    |          |  Gz, Mp  |  Gz, Mp  |  Eb, Ib  |  Ev, Iz  |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                Shift Grp 2                |    AAM   |    AAD   |          |   XLAT/  |
 * D +          +          +          +          +          +          +          +   XLATB  +
 *   |   Eb, 1  |   Ev, 1  |  Eb, CL  |  Ev, CL  |    Ib    |    Ib    |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |  LOOPNE/ |  LOOPE/  |   LOOP   |   JeCXZ  |          IN         |         OUT         |
 * E +  LOOPNZ  +  LOOPZ   +          +          +          +          +          +          +
 *   |    Jb    |    Jb    |    Jb    |    Jb    |  AL, Ib  | eAX, Ib  |  Ib, AL  |  Ib, eAX |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |          |          |          |   REP/   |          |          |     Unary Grp 3     |
 * F +   LOCK   +          +  REPNE   +   REPE   +    HLT   +    CMC   +          +          +
 *   | (Prefix) |          |          | (Prefix) |          |          |    Eb    |    Ev    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 */

/*                                   One-byte Opcode Map (0x08 - 0xFF)
 *         0          1          2          3          4          5          6          7
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                                OR                               |          |  2-byte  |
 * 0 +          +          +          +          +          +          + PUSH CS  +  escape  +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               SBB                               |          |          |
 * 1 +          +          +          +          +          +          + PUSH DS  +  POP DS  +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               SUB                               |          |          |
 * 2 +          +          +          +          +          +          + SEG = CS +   DAS    +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  | (Prefix) |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               CMP                               |          |          |
 * 3 +          +          +          +          +          +          + SEG = DS +   AAS    +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  AL, Ib  | eAX, Iz  | (Prefix) |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                                  DEC general register                                 |
 * 4 +          +          +          +          +          +          +          +          +
 *   |    eAX   |   eCX    |    eDX   |   eBX    |   eSP    |   eBP    |   eSI    |   eDI    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                               POP into general register                               |
 * 5 +          +          +          +          +          +          +          +          +
 *   |    eAX   |   eCX    |    eDX   |   eBX    |    eSP   |   eBP    |   eSI    |   eDI    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |   PUSH   |  IMUL    |   PUSH   |   IMUL   |   INS/   | INS/W/D  |  OUTS/B  | OUTS/W,D |
 * 6 +          + Gv, Ev,  +          +  Gv, Ev, +   INSB   +          +          +          +
 *   |    Iz    |   Iz     |    Ib    |    Ib    |  Yb, DX  |  Yz, DX  |  DX, Xb  |  DX, Xz  |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                       Jcc - Short-displacement jump on condition                      |
 * 7 +     S    +     NS   +    P/PE  +  NP/PO   +   L/NGE  +   NL/GE  +  LE/NG   +  NLE/G   +
 *   |    Jb    |    Jb    |    Jb    |   Jb     |    Jb    |    Jb    |    Jb    |    Jb    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                    MOV                    |    MOV   |    LEA   |    MOV   |  Grp 1A  |
 * 8 +          +          +          +          +          +          +          +    POP   +
 *   |  Eb, Gb  |  Ev, Gv  |  Gb, Eb  |  Gv, Ev  |  Ev, Sw  |   Gv, M  |  Sw, Ew  |    Ev    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |   CBW/   |   CWD/   | far CALL |  FWAIT/  |  PUSHF/D |  POPF/D  |   SAHF   |   LAHF   |
 * 9 +   CWDE/  +   CDQ/   +          +   WAIT   +          +          +          +          +
 *   |   CDQE   |   CQO    |    Ap    |          |    Fv    |    Fv    |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |        TEST         |  STOS/B  | STOS/W/D |  LODS/B  | LODS/W/D |  SCAS/B  | SCAS/W/D |
 * A +          +          +          +          +          +          +          +          +
 *   |  AL, Ib  | eAX, Iz  |  Yb, AL  | Yv, eAX  |  AL, Xb  | eAX, Xv  |  AL, Yb  | eAX, Yv  |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |               MOV immediate word or double into word or double register               |
 * B +          +          +          +          +          +          +          +          +
 *   |    eAX   |   eCX    |   eDX    |   eBX    |    eSP   |    eBP   |    eSI   |   eDI    |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |   ENTER  |          |       far RET       |          |   INT    |          |          |
 * C +          +  LEAVE   +          +          +  INT 3   +          +   INTO   +  IRET/D  +
 *   |  Iw, Ib  |          |    Iw    |          |          |    Ib    |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |                      ESC (Escape to coprocessor instruction set)                      |
 * D +          +          +          +          +          +          +          +          +
 *   |          |          |          |          |          |          |          |          |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |   near   |              JMP               |          IN         |         OUT         |
 * E +   CALL   +          +          +          +          +          +          +          +
 *   |    Jz    |    Jz    |    Ap    |    Jb    |  AL, DX  | eAX, DX  |  DX, AL  | DX, eAX  |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 *   |          |          |          |          |          |          |       INC/DEC       |
 * F +   CLC    +   STC    +   CLI    +    STI   +   CLD    +   STD    +          +          +
 *   |          |          |          |          |          |          |  Grp 4   |   Grp 5  |
 *   +----------+----------+----------+----------+----------+----------+----------+----------+
 */
 
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
