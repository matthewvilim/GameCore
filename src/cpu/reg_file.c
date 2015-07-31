#include "reg_file.h"

#define X86_REG_EFLAGS_INIT        BIT_FIELD_WRITE(0, X86_EFLAGS_MASK_RES0, 1)
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

static INLINE_FORCE void
_reset(reg_file_t *reg_file, mmu_t *mmu) {
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
reg_file_init(reg_file_t *reg_file) {
    ASSERT(reg_file);

}

void
reg_file_reset(reg_file_t *reg_file, mmu_t *mmu) {
    ASSERT(reg_file);

    _reset(reg_file, mmu);
}
