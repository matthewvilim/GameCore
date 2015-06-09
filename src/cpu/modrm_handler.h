/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/decode.h
 */

#ifndef OP_HANDLER_H
#define OP_HANDLER_H

typedef void (*decode_t)(const cpu_t *cpu, instr_t *instr, operand_t *operand);

#endif
