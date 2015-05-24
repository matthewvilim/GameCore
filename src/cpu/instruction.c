/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instruction.c
 */
 
const op_group_t add = {
    .name = "add"
};

const op_info_t add_eb_gb = {
    .group = add,
    .src = AddressingCodeE,
    .dst = AddressingCodeG,
    .operand_code = OperandCodeB,
    .register_code = RegisterCodeNone
};

const op_info_t op_table[] = {
    add_eb_gb, // 0x00
    
}

#endif
