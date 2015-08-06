/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/cpu.c
 */

#include "_cpu.h"

gc_error_t
cpu_init(cpu_t *cpu, mem_t *mem) {
    ASSERT(cpu && mem);

    reg_file_init(&cpu->reg_file);
    mmu_init(&cpu->mmu, mem);

    return GC_NO_ERROR;
}

gc_error_t
cpu_term(cpu_t *cpu) {
    ASSERT(cpu);

    mmu_term(cpu->mmu);

    return GC_NO_ERROR;
}

void
_emulate(cpu_t *cpu, size_t cycles) {

}
