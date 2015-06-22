/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/decode.c
 */

#include "op_handler.h"

addr_offset_t
calc_addr16_base(const *) {
    return { .w = cpu_gen_read_w(cpu, operand->modrm.base) };
}

addr_offset_t
calc_addr16_offset(const cpu_t *cpu, const operand_t *operand) {
    return { .w = operand->modrm.disp16 };
}

addr_offset_t
calc_addr16_base_offset() {
    return { .w = cpu_gen_read_w(cpu, operand->modrm.base) + operand->modrm.disp16 };
}

addr_offset_t
calc_addr16_base_index() {
    return { .w = cpu_gen_read_w(cpu, operand->modrm.base) +
                  cpu_gen_read_w(cpu, operand->modrm.index) };
}

addr_offset_t
calc_addr16_base_index_offset() {
    return { .w = cpu_gen_read_w(cpu, operand->modrm.base) +
                  cpu_gen_read_w(cpu, operand->modrm.index) +
                  operand->modrm.disp16 };
}

addr_offset_t
calc_addr32_scale_index_base() {
    return { .dw = cpu_gen_read_dw(cpu, instr->modrm.base) +
                  (cpu_gen_read_dw(cpu, instr-modrm.index) << instr->modrm.scale) +
                   instr->modrm.disp32 };
}


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
