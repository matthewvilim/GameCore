#include "reg_file.h"

#define X86_REGEFLAGS_INIT        BIT_FIELD_WRITE(0, X86_EFLAGS_MASK_RES0, 1)
#define X86_REG_EIP_INIT           0xFFF0
#define X86_REG_CS_INIT            0x0
#define X86_REG_DS_INIT            0x0
#define X86_REG_ES_INIT            0x0
#define X86_REG_SS_INIT            0x0
#define X86_REG_FS_INIT            0x0
#define X86_REG_GS_INIT            0x0
#define X86_REG_IDTR_INIT_BASE     0x0
#define X86_REG_IDTR_INIT_LIMIT    0x3FF

#define X86_DEV_ID_386 0x3
#define X86_386_STEP_ID 0x0

struct reg_file {
    udword eax, ebx, ecx, edx, esp, edi, esp, ebp, eip, eflags;

    uword fs, gs, cs, ss, ds, es;

    udword eip;

    reg_desc_table gdtr, ldtr, idtr;

    reg_task tr;
    uword cr0, cr1, cr2, cr3;
};

ubyte
reg_file_read_gen_b(const reg_file *rf, const reg r) {
    switch (r) {
        case REG_AL: return BIT_FIELD_READ(rf->eax, MASK_LOW_B);
        case REG_AH: return BIT_FIELD_READ(rf->eax, MASK_HIGH_B);
        case REG_BL: return BIT_FIELD_READ(rf->ebx, MASK_LOW_B);
        case REG_BH: return BIT_FIELD_READ(rf->ebx, MASK_HIGH_B);
        case REG_CL: return BIT_FIELD_READ(rf->ecx, MASK_LOW_B);
        case REG_CH: return BIT_FIELD_READ(rf->ecx, MASK_HIGH_B);
        case REG_DL: return BIT_FIELD_READ(rf->edx, MASK_LOW_B);
        case REG_DH: return BIT_FIELD_READ(rf->edx, MASK_HIGH_B);
        case REG_ZERO: return 0;
    }
}

void
reg_file_write_gen_b(reg_file *rf, const reg r, const val) {
    switch (r) {
        case REG_GEN_AL: BIT_FIELD_WRITE(rf->eax, MASK_LOW_B, val);
        case REG_GEN_AH: BIT_FIELD_WRITE(rf->eax, MASK_HIGH_B, val);
        case REG_GEN_BL: BIT_FIELD_WRITE(rf->ebx, MASK_LOW_B, val);
        case REG_GEN_BH: BIT_FIELD_WRITE(rf->ebx, MASK_HIGH_B, val);
        case REG_GEN_CL: BIT_FIELD_WRITE(rf->ecx, MASK_LOW_B, val);
        case REG_GEN_CH: BIT_FIELD_WRITE(rf->ecx, MASK_HIGH_B, val);
        case REG_GEN_DL: BIT_FIELD_WRITE(rf->edx, MASK_LOW_B, val);
        case REG_GEN_DH: BIT_FIELD_WRITE(rf->edx, MASK_HIGH_B, val);
        default: // throw
    }
}

uword_t
reg_file_ip_read(const reg_file *reg_file) {
    return BIT_FIELD_READ(reg_file->eip, MASK_LOW_W);
}

void
reg_file_ip_write(reg_file *reg_file, uword val) {
    BIT_FIELD_WRITE(reg_file->eip, MASK_LOW_W, val);
}

uword_t
reg_file_flags_read(const reg_file *reg_file) {
 return BIT_FIELD_READ(reg_file->eflags, MASK_LOW_W);
}

void
reg_file_flags_write(reg_file *reg_file, uword val) {
    BIT_FIELD_WRITE(reg_file->eflags, MASK_LOW_W, val);
}

C86_INLINE bool
reg_file_pe_enabled(const reg_file *reg_file) {
    return reg_file->cr0 & X86_CR0_MASK_PE;
}

C86_INLINE bool
reg_file_vm_enabled(const reg_file *reg_file) {
    return reg_file->eflags & X86_EFLAGS_MASK_VM;
}

static INLINE_FORCE void
_reset(reg_file *reg_file, mmu *mmu) {
    reg_file_gen_write_dw(reg_file, REG_GEN_ZERO, 0);

    reg_file_gen_write_b(reg_file, X86_REG_DH, X86_DEV_ID_386);
    reg_file_gen_write_b(reg_file, X86_REG_DL, X86_386_STEP_ID);

    reg_file->eflags = X86_REG_EFLAGS_INIT;

    reg_file->eip = X86_REG_EIP_INIT;

    reg_file_seg_write(reg_file, X86_REG_CS, X86_REG_CS_INIT);
    reg_file_seg_write(reg_file, X86_REG_DS, X86_REG_DS_INIT);
    reg_file_seg_write(reg_file, X86_REG_ES, X86_REG_ES_INIT);
    reg_file_seg_write(reg_file, X86_REG_SS, X86_REG_SS_INIT);
    reg_file_seg_write(reg_file, X86_REG_FS, X86_REG_FS_INIT);
    reg_file_seg_write(reg_file, X86_REG_GS, X86_REG_GS_INIT);
    for (int i = 0; i < ARRAY_SIZE(reg_file->seg); i++) {
        reg_file_cache_seg_desc(reg_file, i, true, mmu);
    }

    reg_file->idtr = { .base = X86_REG_IDTR_INIT_BASE; .limit = X86_REG_IDTR_INIT_LIMIT };

    reg_file->cr0 =
}

void
reg_file_init(reg_file *reg_file) {
    ASSERT(reg_file);

}

void
reg_file_reset(reg_file *reg_file, mmu *mmu) {
    ASSERT(reg_file);

    _reset(reg_file, mmu);
}
