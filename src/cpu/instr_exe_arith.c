/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instr_arith.c
 */

#include "instr_exe_inline.h"

#define ADD(op1, op2) ((op1) + (op2))

void
instr_exe_add_Eb_Gb(cput_t *cpu, const instr_t *instr) {
    ASSERT(cpu && instr);
    
    addr_seg_offset_t addr;
    byte_t op1 = _operand_read_Eb(cpu, instr, &addr);
    byte_t op2 = _operand_read_Gb(cpu, instr);
    byte_t result = ADD(op1, op2);

    _operand_write_Eb(cpu, instr, addr, result);
}
