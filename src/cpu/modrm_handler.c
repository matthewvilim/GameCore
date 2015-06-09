/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/decode.c
 */

#include "op_handler.h"

GC_INLINE void
op_handler_Sb(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    operand->b = cpu_gen_b_host(cpu, instr->modrm_reg);
    instr->modrm_reg = BIT_FIELD_READ(instr->addr[1], X86_MODRM_REG_MASK);
    operand->handler = op_handler_S(cpu, instr, operand);
}

GC_INLINE void *
decode_G(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    instr->modrm_reg = BIT_FIELD_READ(instr->addr[1], X86_MODRM_REG_MASK);

}
