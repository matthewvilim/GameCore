#include "decode.h"

enum size_attribute {
    SIZE_ATTRIBUTE_SEG_DEFAULT = 1 << 0,
    SIZE_ATTRIBUTE_OPERAND_PREFIX = 1 << 1,
    SIZE_ATTRIBUTE_ADDRESS_PREFIX = 1 << 2
};

enum operand_size {
    OPERAND_SIZE16,
    OPERAND_SIZE32
};

enum address_size {
    ADDRESS_SIZE16,
    ADDRESS_SIZE32
};

struct decode {
    operand_size op_size;
    address_size addr_size;
};

enum operand_size _operand_size_table[] = {
    []                                                                                           = OPERAND_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT]                                                                 = OPERAND_SIZE32,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = OPERAND_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = OPERAND_SIZE16,
    [                                                             SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT |                                 SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE32,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE16
}

enum address_size _operand_size_table[] = {
    []                                                                                           = ADDRESS_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT]                                                                 = ADDRESS_SIZE32,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = ADDRESS_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = ADDRESS_SIZE32,
    [                                                             SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT |                                 SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE16,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE16
}

typedef enum _op {
    OP_ADD,
    OP_XOR
} _op_t;

typedef struct _opcode {
    _op_t op;
    uint8_t s : 1;
    uint8_t d : 1;
} _opcode_t;

typedef struct _modrm {
    uint8_t mod : 2;
    uint8_t reg : 3;
    uint8_t rm : 3;
} _modrm_t;

typedef struct _sib {
    uint8_t ss : 2;
    uint8_t index : 3;
    uint8_t base : 3;
} _sib_t;

typedef struct _decode {
    ubyte_t prefix_count;
    ubyte_t prefix[4];


    _modrm_t modrm;
    _sib_t sib;
} _decode_t;

typedef struct _addr {
    reg base, index;
    unsigned int scale : 2;
    enum { DISP_B, DISP_W, DISP_DW } disp;
} _addr;

typedef struct operand {
    struct *operand;
    union {
        addr *table;
        struct {
            op_handler handler;
            union {
                reg reg;
                _addr addr;
            };
        };
    };
} modrm;

typedef struct sib {
    op_handler handler;
    addr addr;
};
