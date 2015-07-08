/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instr_calc_addr.h
 */

 #ifndef INSTR_CALC_ADDR
 #define INSTR_CALC_ADDR

typedef struct cpu cpu_t;
typedef struct instr instr_t;

dword_t instr_calc_addr16_base(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr16_offset(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr16_base_offset(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr16_base_index(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr16_base_index_offset(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr32_base(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr32_offset(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr32_base_offset(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr32_scale_index_base(const cpu_t *cpu, const instr_t *instr;
dword_t instr_calc_addr32_scale_index_offset(const cpu_t *cpu, const instr_t *instr);
dword_t instr_calc_addr32_scale_index_base_offset(const cpu_t *cpu, const instr_t *instr);

#endif
