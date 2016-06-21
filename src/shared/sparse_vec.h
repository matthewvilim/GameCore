#ifndef SPARSE_VEC_H
#define SPARSE_VEC_H

struct sparse_vec {
    void **blocks;
    size_t block_size, size, block_count;
};


#endif
