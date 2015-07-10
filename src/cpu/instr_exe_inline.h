#ifndef INSTR_EXE_INLINE_H
#define INSTR_EXE_INLINE_H

#include "instr_exe.h"

GC_INLINE byte_t
_operand_read_Eb(const cpu_t *cpu,
                 const instr_t *instr,
                 addr_seg_offset_t *addr) {
    if (instr->resolve) {
        addr->seg = instr->seg;
        addr->offset = instr->resolve(instr);
        cpu->mem.read.b(cpu->mem, addr);
    } else {
        return cpu_gen_read_b(cpu, instr->rm);
    }
}

GC_INLINE byte_t
_operand_read_Gb(const cpu_t *cpu,
                 const instr_t *instr) {
    return cpu_gen_read_b(cpu, instr->reg);
}

GC_INLINE void
_operand_write_Eb(const cpu_t *cpu,
                  const instr_t *instr,
                  addr_seg_offset_t *addr,
                  byte_t val) {
    if (instr->resolve) {
        cpu->mem.write.b(cpu->mem, &addr, val);
    } else {
        cpu_gen_write_b(cpu, instr->rm, val);
    }
}

#endif
