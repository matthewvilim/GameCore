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

GC_INLINE void
_read_reg_b(const cpu_t *cpu, operand_t *operand, const uint8_t reg) {
    operand->reg = reg;
    cpu_gen_read_b(cpu, operand->reg);
}

GC_INLINE void
_read_reg_w(const cpu_t *cpu, operand_t *operand, const uint8_t reg) {
    operand->reg = reg;
    cpu_gen_read_w(cpu, operand->reg);
}

GC_INLINE void
_read_ob(const cpu_t *cpu, operand_t *operand, const lin_addr_t instr_addr) {
    operand->addr = instr_addr;
    operand->addr.offset++;
    lin_addr_t addr;
    addr.base =
    addr.offset = mem_read_w(mem, operand->addr);
    operand->b = mem_read_b(mem, addr);
}

GC_INLINE void
_read_ow(const cpu_t *cpu, operand_t *operand, const lin_addr_t instr_addr) {
    operand->addr = instr_addr;
    operand->addr.offset++;
    addr.base =
    addr.offset = mem_read_w(mem, operand->addr);
    operand->w = mem_read_w(mem, addr);
}

GC_INLINE void
_read_ib(const cpu_t *cpu, operand_t *operand, const lin_addr_t instr_addr) {
    operand->addr = instr_addr;
    operand->addr.offset++;
    operand->b = mem_read_b(mem, operand->addr);
}

GC_INLINE void
_read_iw(const cpu_t *cpu, operand_t *operand, const lin_addr_t instr_addr) {
    operand->addr = instr_addr;
    operand->addr.offset++;
    operand->w = mem_read_w(mem, operand->addr);
}

void
_read_dummy(const cpu_t *cpu, instr_t *instr) {};

void
_exe_dummy(const cpu_t *cpu, instr_t *instr) {};

void
_write_dummy(const cpu_t *cpu, instr_t *instr) {};

// Eb Gb
void

// AL Ob
void
_read_al_ob(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_AL);
    _read_ob(cpu, &instr->op2, instr->instr_addr);
}

// Ob AL
void
_read_ob_al(const cpu_t *cpu, instr_t *instr) {
    _read_ob(cpu, &instr->op1, instr->instr_addr)
    _read_reg_b(cpu, &instr->op2, X86_REG_AL);
}

// AX Ow
void
_read_ax_ow(const cpu_t *cpu, instr_t *instr) {
    _read_reg_w(cpu, &instr->op1, X86_REG_AX);
    _read_ow(cpu, &instr->op2, instr->instr_addr);
}

// Ow AX
void
_read_ow_ax(const cpu_t *cpu, instr_t *instr) {
    _read_ow(cpu, &instr->op1, instr->instr_addr);
    _read_reg_w(cpu, &instr->op2, X86_REG_AX);
}

// AL Ib
void
_read_al_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_AL);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

// CL Ib
void
_read_cl_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_CL);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

// DL Ib
void
_read_dl_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_DL);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

// BL Ib
void
_read_bl_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_BL);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

// AH Ib
void
_read_ah_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_AH);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

// CH Ib
void
_read_ch_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_CH);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

// DH Ib
void
_read_dh_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_DH);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

// BH Ib
void
_read_bh_ib(const cpu_t *cpu, instr_t *instr) {
    _read_reg_b(cpu, &instr->op1, X86_REG_BH);
    _read_ib(cpu, &instr->op2, instr->instr_addr);
}

void _write_reg_b(cpu_t *cpu, const instr_t *instr) {
    cpu_gen_write_b(cpu, instr->op1.reg, instr->result.b);
}

void _write_reg_w(cpu_t *cpu, const instr_t *instr) {
    cpu_gen_write_w(cpu, instr->op1.reg, instr->result.w);
}

#endif
