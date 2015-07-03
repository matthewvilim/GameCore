/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instruction.c
 */

const op_group_t mov = {
    .name = "mov"
};

const op_info_t mov_al_ob = {
    .read = _read_al_ob;
    .exe = _exe_dummy;
    .write =
};

const op_info_t op_table[] = {
    , // 0x00

}
