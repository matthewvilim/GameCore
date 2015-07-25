/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/reg_file.h
 */

 #ifndef REG_FILE_H
 #define REG_FILE_H

 typedef struct reg_file {
     udword_t gen[8], eip, eflags;

     uword_t seg[6];

     udword_t eip;

     struct gdtr {
         uword_t size;
         addr_lin_t base;
     };

     struct ldtr {
         uword_t limit;
         addr_lin_t base;
     };

     struct idtr {
         uword_t limit;
         addr_lin_t base;
     };

     uword_t cr0, cr1, cr2, cr3, tr;
 } reg_file_t;

void reg_file_init(cpu_t *cpu);

// EIP
C86_INLINE udword_t
cpu_eip_read(const cpu_t *cpu) {
 return cpu->reg_file.eip, MASK_DW;
}

C86_INLINE uword_t
cpu_ip_read(const cpu_t *cpu) {
 return BIT_FIELD_READ(cpu->reg_file.eip, MASK_LOW_W);
}

C86_INLINE void
cpu_eip_write(cpu_t *cpu, udword_t val) {
 cpu->reg_file.eip = val;
}

C86_INLINE void
cpu_ip_write(cpu_t *cpu, uword_t val) {
 BIT_FIELD_WRITE(cpu->reg_file.eip, MASK_LOW_W, val);
}

// EFLAGS
C86_INLINE udword_t
cpu_eflags_read(const cpu_t *cpu) {
 return cpu->reg_file.eflags;
}

C86_INLINE uword_t
cpu_flags_read(const cpu_t *cpu) {
 return BIT_FIELD_READ(cpu->reg_file.eflags, MASK_LOW_W);
}

C86_INLINE void
cpu_eflags_write(cpu_t *cpu, udword_t val) {
 cpu->reg_file.eflags = val;
}

C86_INLINE void
cpu_flags_write(cpu_t *cpu, uword_t val) {
 BIT_FIELD_WRITE(cpu->reg_file.eflags, MASK_LOW_W, val);
}

// general registers
C86_INLINE ubyte_t
cpu_gen_read_b(const cpu_t *cpu, const uint8_t reg) {
 udword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
 return BIT_FIELD_READ(cpu->reg_file.gen[reg & ~BIT(2)], mask);
}

C86_INLINE uword_t
cpu_gen_read_w(const cpu_t *cpu, const uint8_t reg) {
 return BIT_FIELD_READ(cpu->reg_file.gen[reg], MASK_LOW_W);
}

C86_INLINE udword_t
cpu_gen_read_dw(const cpu_t *cpu, const uint8_t reg) {
 return cpu->reg_file.gen[reg];
}

C86_INLINE void
cpu_gen_write_b(cpu_t *cpu, const uint8_t reg, ubyte_t val) {
 udword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
 BIT_FIELD_WRITE(cpu->reg_file.gen[reg & ~BIT(2)], mask, val);
}

C86_INLINE void
cpu_gen_write_w(cpu_t *cpu, const uint8_t reg, uword_t val) {
 BIT_FIELD_WRITE(cpu->reg_file.gen[reg], MASK_LOW_W, val);
}

C86_INLINE void
cpu_gen_write_dw(cpu_t *cpu, const uint8_t reg, udword_t val) {
 cpu->reg_file.gen[reg] = val;
}

// segment registers
C86_INLINE uword_t
cpu_seg_read(const cpu_t *cpu, const uint8_t reg) {
 return cpu->reg_file.seg[reg];
}

C86_INLINE void
cpu_seg_write(cpu_t *cpu, const uint8_t reg, uword_t val) {
 if (cpu_vm_enabled(cpu)) {
     cpu->reg_file.seg[reg].Selector = vale;
 } else {

 }
 cpu->reg_file.seg[reg] = val;
}

 #endif
