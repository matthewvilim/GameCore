/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instr_calc_exe.h
 */

 #ifndef INSTR_CALC_ADDR
 #define INSTR_CALC_ADDR

typedef struct cpu cpu;
typedef struct instr instr;

typedef void instr_exe_t(cpu *cpu, const instr *instr);

void instr_exe_add_gen_b_gen_b(cput *cpu, const instr *instr);

#endif
