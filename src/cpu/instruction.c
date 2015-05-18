/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instruction.c
 */

// EAX
static const reg_gen_t reg_eax = { .idx = REG_GEN_IDX_EAX, .mask = MASK_LONG };
static const reg_gen_t reg_ax  = { .idx = REG_GEN_IDX_EAX, .mask = MASK_LOW_W };
static const reg_gen_t reg_al  = { .idx = REG_GEN_IDX_EAX, .mask = MASK_LOW_B };
static const reg_gen_t reg_ah  = { .idx = REG_GEN_IDX_EAX, .mask = MASK_HIGH_B };
// EBX
static const reg_gen_t reg_ebx = { .idx = REG_GEN_IDX_EBX, .mask = MASK_LONG };
static const reg_gen_t reg_bx  = { .idx = REG_GEN_IDX_EBX, .mask = MASK_LOW_W };
static const reg_gen_t reg_bl  = { .idx = REG_GEN_IDX_EBX, .mask = MASK_LOW_B };
static const reg_gen_t reg_bh  = { .idx = REG_GEN_IDX_EBX, .mask = MASK_HIGH_B };
// ECX
static const reg_gen_t reg_ecx = { .idx = REG_GEN_IDX_ECX, .mask = MASK_LONG };
static const reg_gen_t reg_cx  = { .idx = REG_GEN_IDX_ECX, .mask = MASK_LOW_W };
static const reg_gen_t reg_cl  = { .idx = REG_GEN_IDX_ECX, .mask = MASK_LOW_B };
static const reg_gen_t reg_ch  = { .idx = REG_GEN_IDX_ECX, .mask = MASK_HIGH_B };
// EDX
static const reg_gen_t reg_edx = { .idx = REG_GEN_IDX_EDX, .mask = MASK_LONG };
static const reg_gen_t reg_dx  = { .idx = REG_GEN_IDX_EDX, .mask = MASK_LOW_W };
static const reg_gen_t reg_dl  = { .idx = REG_GEN_IDX_EDX, .mask = MASK_LOW_B };
static const reg_gen_t reg_dh  = { .idx = REG_GEN_IDX_EDX, .mask = MASK_HIGH_B };
// ESP
static const reg_gen_t reg_esp = { .idx = REG_GEN_IDX_ESP, .mask = MASK_LONG };
static const reg_gen_t reg_sp  = { .idx = REG_GEN_IDX_ESP, .mask = MASK_LOW_W };
// EBP
static const reg_gen_t reg_ebp = { .idx = REG_GEN_IDX_EBP, .mask = MASK_LONG };
static const reg_gen_t reg_bp  = { .idx = REG_GEN_IDX_EBP, .mask = MASK_LOW_W };
// ESI
static const reg_gen_t reg_esi = { .idx = REG_GEN_IDX_ESI, .mask = MASK_LONG };
static const reg_gen_t reg_si  = { .idx = REG_GEN_IDX_ESI, .mask = MASK_LOW_W };
// EDI
static const reg_gen_t reg_edi = { .idx = REG_GEN_IDX_EDI, .mask = MASK_LONG };
static const reg_gen_t reg_di  = { .idx = REG_GEN_IDX_EDI, .mask = MASK_LOW_W };

const reg_gen_t modrm_byte[] {
    reg_al,
    reg_cl,
    reg_bl,
    reg_dl,
    reg_ah,
    reg_ch,
    reg_bh,
    reg_dh
};

const reg_gen_t modrm_word[] {
    reg_ax,
    reg_cx,
    reg_bx,
    reg_dx,
    reg_sp,
    reg_bp,
    reg_si,
    reg_di
};

const reg_gen_t modrm_dword[] {
    reg_eax,
    reg_ecx,
    reg_ebx,
    reg_edx,
    reg_esp,
    reg_ebp,
    reg_esi,
    reg_edi
};
 
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
 *         8          9          A          B          C          D          E          F
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

static const op_group_t add = {
    .name = "add"
};

static const op_info_t add_eb_gb = {
    .group = add,
    .addressing = ADDRESSING_E | ADDRESSING_G,
    .operant = OPERANT_B,
    .dir = DIR_REG_TO_RM
};

static const op_info_t op_table[] = {
    add_eb_gb, // 0x00
    
}

#endif
