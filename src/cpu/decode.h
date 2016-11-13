#ifndef DECODE_H
#define DECODE_H

enum size_attribute {
    SIZE_ATTRIBUTE_SEG_DEFAULT = 1 << 0,
    SIZE_ATTRIBUTE_OPERAND_PREFIX = 1 << 1,
    SIZE_ATTRIBUTE_ADDRESS_PREFIX = 1 << 2
};

enum operand_size {
    OPERAND_SIZE8,
    OPERAND_SIZE16,
    OPERAND_SIZE32
};

enum address_size {
    ADDRESS_SIZE16,
    ADDRESS_SIZE32
};

enum prefix_instr {
    PREFIX_INSTR_NONE,
    PREFIX_INSTR_REP,
    PREFIX_INSTR_REPE_REPZ,
    PREFIX_INSTR_REPNE_REPNZ,
    PREFIX_INSTR_LOCK
};

struct decode {
    enum prefix_instr prefix_instr;
    bool prefix_address_size, prefix_operand_size, prefix_seg;
    reg_file_seg prefix_seg;

    operand_size op_size;
    address_size addr_size;
};

#endif
