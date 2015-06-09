/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MACROS_H
#define MACROS_H

/*********************
 * SIZE CALCULATIONS *
 ********************/
#define ARRAY_SIZE(array)            (sizeof(array) / sizeof(array[0]))
#define MEMBER_SIZE(type, member)    sizeof(((type *)0)->member)

/***************************
 * BIT MANIPULATION MACROS *
 **************************/
// create masks
#define BIT(i)                   (1 << i)
#define MASK_LEN(len, low)       ((BIT(len) - 1) << (low))
#define MASK_RANGE(high, low)    MASK_LEN((high) - (low) + 1, low)
// miscellaneous tricks
#define LOW_BIT(val)        ((val) & -(val))
#define LOW_BIT_IDX(val)    ((val) != 0 ? ((val) / LOW_BIT(val)) : 0)
// read/write masks
#define BIT_FIELD_READ(in, mask)         (((in) & (mask)) >> LOW_BIT_IDX(mask))
#define BIT_FIELD_WRITE(in, mask, val)    (((in) & ~(mask)) | ((val) << LOW_BIT_IDX(mask)))
#define MASK_CLEAR(in, mask)           BIT_FIELD_WRITE(in, mask, 0)
#define MASK_TEST_VAL(in, mask, val)   (BIT_FIELD_WRITE(0, mask, (val)) == ((in) & (mask)))
// boolean operations
#define MASK_OR_VAL(in, mask, val)     (BIT_FIELD_WRITE(0, mask, (val)) | (in))
#define MASK_AND_VAL(in, mask, val)    (BIT_FIELD_WRITE(0, mask, (val)) & (in))
#define MASK_XOR_VAL(in, mask, val)    (BIT_FIELD_WRITE(0, mask, (val)) ^ (in))

/********************
 * COMMON BIT MASKS *
 ********************/

#ifndef __has_builtin
# define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_bswap32)
# define BYTE_SWAP32(val) __builtin_bswap32(val)
#else
# define BYTE_SWAP32(val) ((((val) & MASK_RANGE(31, 24)) >> 24) \
                         | (((val) & MASK_RANGE(23, 16)) >> 8)  \
                         | (((val) & MASK_RANGE(15, 8))  << 8)  \
                         | (((val) & MASK_RANGE(7, 0))   << 24))
#endif

#if __has_builtin(__builtin_bswap16)
# define BYTE_SWAP16(val) __builtin_bswap16(val)
#else
# define BYTE_SWAP16(val) ((val >> 8) | (val << 8))
#endif

#define MASK_LOW_B     MASK_RANGE(7, 0)
#define MASK_HIGH_B   (MASK_LOW_B << 8)
#define MASK_W        (MASK_LOW_B | MASK_HIGH_B)

#if

#if GC_ARCH_NATIVE_BIG_ENDIAN
# define ENDIAN_CONV_DWORD(val)   BYTE_SWAP32(val)
# define ENDIAN_CONV_WORD(val)    BYTE_SWAP16(val)
#else
# define ENDIAN_CONV_DWORD(val)   (val)
# define ENDIAN_CONV_WORD(val)    (val)
#endif

#endif
