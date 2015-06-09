/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/decode.c
 */

#include "decode.h"

GC_INLINE void
_decode_eXX(const cpu_t *cpu, instr_t *instr, operand_t *operand, uint8_t reg) {
    switch (instr->op_size) {
        case OpSizeW:
            operand->w = cpu_gen_w_host(cpu, X86_REG_AX);
            break;
        case OpSizeDW:
            operand->dw = cpu_gen_dw_host(cpu, X86_REG_EAX);
            break;
    }
}

GC_INLINE void
_decode_XX(const cpu_t *cpu, instr_t *instr, operand_t *operand, uint8_t reg) {
    operand->b = cpu_gen_b_host(cpu, reg);
}

void
decode_I(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    operand->host = instr->opcode + instr->modrm_len + 1;
}

void
decode_S(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    uint8_t gen = BIT_FIELD_READ(instr->opcode[1], X86_MODRM_REG_MASK);
    operand->w = cpu_seg_host(cpu, gen);
}

void
decode_Gb(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    uint8_t gen = BIT_FIELD_READ(instr->opcode[1], X86_MODRM_REG_MASK);
    operand->b = cpu_gen_b_host(cpu, gen);
}

void
decode_Gv(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    uint8_t gen = BIT_FIELD_READ(instr->opcode[1], X86_MODRM_REG_MASK);
    switch (instr->op_size) {
        case OpSizeW:
            operand->w = cpu_gen_w_host(cpu, gen);
            break;
        case OpSizeDW:
            operand->dw = cpu_gen_dw_host(cpu, gen);
            break;
    }
}

void
decode_eAX(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    _decode_eXX(cpu, instr, operand, X86_REG_EAX);
}

void
decode_eBX(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    _decode_eXX(cpu, instr, operand, X86_REG_EBX);
}

void
decode_AL(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    _decode_XX(cpu, instr, operand, X86_REG_AL);
}
