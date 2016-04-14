/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instr_arith.c
 */

#include "instr_exe_inline.h"

#define ADD(op1, op2) ((op1) + (op2))

void
instr_exe_add_gen_b_gen_b(cput *cpu, const instr *instr) {
    ASSERT(cpu && instr);

    ubyte op1 = _operand_read_gen_b(cpu, instr, &addr);
    ubyte op2 = _operand_read_gen_b(cpu, instr);
    ubyte result = ADD(op1, op2);

    _operand_write_gen_b(cpu, instr, result);
}
