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

void instr_exe_add_Eb_Gb(cput_t *cpu, const instr_t *instr);

#endif
