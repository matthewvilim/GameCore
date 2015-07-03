/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/decode.c
 */

calc_addr_t calc_addr16_table_modrm[] = {
    calc_addr16_base_index, // Mod 0x0 - Reg 0x0 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index, // Mod 0x0 - Reg 0x1 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index, // Mod 0x0 - Reg 0x2 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index, // Mod 0x0 - Reg 0x3 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index, // Mod 0x0 - Reg 0x4 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index, // Mod 0x0 - Reg 0x5 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index, // Mod 0x0 - Reg 0x6 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index, // Mod 0x0 - Reg 0x7 - R/M 0x0-0x7
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base_index,
    calc_addr16_base,
    calc_addr16_base,
    calc_addr16_offset,
    calc_addr16_base,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x0 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x1 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x2 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x3 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x4 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x5 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x6 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x1 - Reg 0x7 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x0 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x1 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x2 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x3 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x4 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x5 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x6 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_index_offset, // Mod 0x2 - Reg 0x7 - R/M 0x0-0x7
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_index_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset,
    calc_addr16_base_offset
}

calc_addr_t calc_addr32_table_modrm[] = {
    calc_addr32_base, // Mod 0x0 - Reg 0x0 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base, // Mod 0x0 - Reg 0x1 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base, // Mod 0x0 - Reg 0x2 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base, // Mod 0x0 - Reg 0x3 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base, // Mod 0x0 - Reg 0x4 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base, // Mod 0x0 - Reg 0x5 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base, // Mod 0x0 - Reg 0x6 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base, // Mod 0x0 - Reg 0x7 - R/M 0x0-0x7
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base,
    NULL,
    calc_addr32_offset,
    calc_addr32_base,
    calc_addr32_base,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x0 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x1 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x2 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x3 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x4 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x5 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x6 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x1 - Reg 0x7 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x0 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x1 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x2 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x3 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x4 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x5 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x6 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset, // Mod 0x2 - Reg 0x7 - R/M 0x0-0x7
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    NULL,
    calc_addr32_base_offset,
    calc_addr32_base_offset,
    calc_addr32_base_offset
}

calc_addr_t calc_addr32_table_sib[1 << 8][2] = {
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x0 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x1 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x2 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x3 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x4 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_base, calc_addr32_base_offset }, // SS 0x0 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_offset, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x6 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x0 - Index 0x7 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x0 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x1 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x2 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x3 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x4 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_base, calc_addr32_base_offset }, // SS 0x1 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_offset, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x6 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x1 - Index 0x7 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x0 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x1 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x2 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x3 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x4 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_base, calc_addr32_base_offset }, // SS 0x2 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_offset, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x6 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x2 - Index 0x7 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x0 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x1 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x2 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x3 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x4 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_base, calc_addr32_base_offset }, // SS 0x3 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_offset, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_base, calc_addr32_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x5 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x6 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset }, // SS 0x3 - Index 0x7 - Base 0x0-0x7
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_offset, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
    { calc_addr32_scale_index_base, calc_addr32_scale_index_base_offset },
}

dword_t
calc_addr16_base(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_w(cpu, instr->modrm.base);
}

dword_t
calc_addr16_offset(const cpu_t *cpu, const instr_t *instr) {
    return instr->modrm.disp16;
}

dword_t
calc_addr16_base_offset(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_w(cpu, instr->modrm.base) + instr->modrm.disp16;
}

dword_t
calc_addr16_base_index(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_w(cpu, instr->modrm.base) +
           cpu_gen_read_w(cpu, instr->modrm.index);
}

dword_t
calc_addr16_base_index_offset(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_w(cpu, instr->modrm.base) +
           cpu_gen_read_w(cpu, instr->modrm.index) +
                          instr->modrm.disp16;
}

dword_t
calc_addr32_base(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_dw(cpu, instr->modrm.base);
}

dword_t
calc_addr32_offset(const cpu_t *cpu, const instr_t *instr) {
    return instr->modrm.disp32;
}

dword_t
calc_addr32_base_offset(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_dw(cpu, instr->modrm.base) + instr->modrm.disp32;
}

dword_t
calc_addr32_scale_index_base(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_dw(cpu, instr->modrm.base) +
          (cpu_gen_read_dw(cpu, instr-modrm.index) << instr->modrm.scale);
}

dword_t
calc_addr32_scale_index_offset(const cpu_t *cpu, const instr_t *instr) {
    return (cpu_gen_read_dw(cpu, instr-modrm.index) << instr->modrm.scale) +
            instr->modrm.disp32;
}

dword_t
calc_addr32_scale_index_base_offset(const cpu_t *cpu, const instr_t *instr) {
    return cpu_gen_read_dw(cpu, instr->modrm.base) +
          (cpu_gen_read_dw(cpu, instr-modrm.index) << instr->modrm.scale) +
           instr->modrm.disp32;
}
