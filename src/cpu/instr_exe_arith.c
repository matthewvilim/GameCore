/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instr_arith.c
 */

#include "instr_exe.h"

#define ADD(op1, op2) ((op1) + (op2))

void
instr_exe_add_Eb_Gb(cput_t *cpu, const instr_t *instr) {
    addr_seg_offset_t addr;
    byte_t op1 = operand_read_Eb(cpu, instr, &addr);
    byte_t op2 = operand_read_Gb(cpu, instr);
    byte_t result = ADD(op1, op2);

    operand_write_Eb(cpu, instr, addr, result);
}
