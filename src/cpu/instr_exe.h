/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instr_calc_exe.h
 */

 #ifndef INSTR_CALC_ADDR
 #define INSTR_CALC_ADDR

typedef struct cpu cpu_t;
typedef struct instr instr_t;

typedef void (*instr_exe_t)(cpu_t *cpu, const instr_t *instr);

GC_INLINE byte_t
operand_read_Eb(const cpu_t *cpu,
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
operand_read_Gb(const cpu_t *cpu,
                 const instr_t *instr) {
    return cpu_gen_read_b(cpu, instr->reg);
}

GC_INLINE void
operand_write_Eb(const cpu_t *cpu,
                  const instr_t *instr,
                  addr_seg_offset_t *addr,
                  byte_t val) {
    if (instr->resolve) {
        cpu->mem.write.b(cpu->mem, &addr, val);
    } else {
        cpu_gen_write_b(cpu, instr->rm, val);
    }
}

void instr_exe_add_Eb_Gb(cput_t *cpu, const instr_t *instr);

#endif
