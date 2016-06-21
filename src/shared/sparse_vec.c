#include "sparse_vec.h"

void
sparse_vec_init(struct sparse_vec *vec, size_t size, size_t block_size) {
    assert(block_size <= size);

    vec->size = EXP2_CEILING(size);
    vec->block_size = EXP2_CEILING(block_size);
    vec->block_count = vec->size / vec->block_size;
    vec->blocks = malloc(vec->block_count * sizeof(void *));
}

void
sparse_vec_copy(struct sparse_vec *vec, size_t offset, size_t len, bool rw, void *buf) {
    for (size_t i = offset; i < offset + len; i += vec->block_size) {
        size_t block_index = i / block->size;
        size_t block_offset = i % block->size;
        size_t block_len = MIN(offset + len - i, block->size);
        void *block = vec->blocks[block_index];
        if (!block) {
            _block_alloc(vec, block_index);
        }
        void *src = rw ? block + block_offset : buf;
        void *dst = rw ? buf : block + block_offset;
        memcpy(src, dst, block_len);
    }
}

void
sparse_vec_term(struct sparse_vec *vec) {
    for (size_t i = 0; i < vec->block_count; i++) {
        _block_dealloc(vec, i);
    }
    free(vec->blocks);
}

void
_block_alloc(struct sparse_vec *vec, size_t index) {
    void *block = malloc(vec->block_size);
    memzero(block, vec->block_size);
    vec->blocks[index] = block;
}

void
_block_dealloc(struct sparse_vec *vec, size_t index) {
    free(vec->blocks[index]);
}
