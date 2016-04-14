#include "decode.h"

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

typedef struct addr {
    reg base, index;
    unsigned int scale : 2;
    enum { DISP_B, DISP_W, DISP_DW } disp;
};

typedef struct modrm {
    bool sib;
    union {
        addr *table;
        struct {
            addr_handler handler;
            union {
                reg reg;
                addr addr;
            };
        };
    };
} modrm;

typedef struct sib {
    addr_handler handler;
    addr addr;
};
