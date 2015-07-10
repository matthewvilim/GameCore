/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instr_calc_addr.c
 */

#include "cpu_inline.h"

GC_INLINE dword_t
_addr16_base(const cpu_t *cpu, const instr_t *instr) {
     return cpu_gen_read_w(cpu, instr->modrm.m.base);
}

GC_INLINE dword_t
_addr16_index(const cpu_t *cpu, const instr_t *instr) {
      return cpu_gen_read_w(cpu, instr->modrm.m.index);
}

GC_INLINE dword_t
_addr16_offset(const instr_t *instr) {
       return instr->modrm.m.disp16;
}

GC_INLINE dword_t
_addr32_base(const cpu_t *cpu, const instr_t *instr) {
     return cpu_gen_read_dw(cpu, instr->modrm.m.base);
}

GC_INLINE dword_t
_addr32_index(const cpu_t *cpu, const instr_t *instr) {
       return cpu_gen_read_dw(cpu, instr-modrm.m.index) << instr->modrm.m.scale;
}

GC_INLINE dword_t
_addr32_offset(const instr_t *instr) {
       return instr->modrm.m.disp32;
}

dword_t
instr_calc_addr16_base(const cpu_t *cpu, const instr_t *instr) {
    return _addr16_base(cpu, instr);
}

dword_t
instr_calc_addr16_offset(const cpu_t *cpu, const instr_t *instr) {
    return _addr16_offset(instr);
}

dword_t
instr_calc_addr16_base_index(const cpu_t *cpu, const instr_t *instr) {
    return _addr16_base(cpu, instr) + _addr16_index(cpu, instr);
}

dword_t
instr_calc_addr16_base_offset(const cpu_t *cpu, const instr_t *instr) {
    return _addr16_base(cpu, instr) + _addr16_offset(instr);
}

dword_t
instr_calc_addr16_base_index_offset(const cpu_t *cpu, const instr_t *instr) {
    return _addr16_base(cpu, instr) + _addr16_index(cpu, instr) + _addr16_offset(instr);

}

dword_t
instr_calc_addr32_base(const cpu_t *cpu, const instr_t *instr) {
    return _addr32_base(cpu, instr);
}

dword_t
instr_calc_addr32_offset(const cpu_t *cpu, const instr_t *instr) {
    return _addr32_offset(instr);
}

dword_t
instr_calc_addr32_base_index(const cpu_t *cpu, const instr_t *instr) {
    return _addr32_base(cpu, instr) + _addr32_index(cpu, instr);
}

dword_t
instr_calc_addr32_base_offset(const cpu_t *cpu, const instr_t *instr) {
    return _addr32_base(cpu, instr) + _addr32_offset(instr);
}

dword_t
instr_calc_addr32_index_offset(const cpu_t *cpu, const instr_t *instr) {
    return _addr32_index(cpu, instr) + _addr32_offset(instr);
}

dword_t
instr_calc_addr32_base_index_offset(const cpu_t *cpu, const instr_t *instr) {
    return _addr32_base(cpu, instr) + _addr32_index(cpu, instr) + _addr32_offset(instr);
}
