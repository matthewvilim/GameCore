/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MACROS_H
#define MACROS_H

#include "compiler.h"

/*********************
 * SIZE CALCULATIONS *
 ********************/
#define ARRAY_SIZE(array)            (sizeof(array) / sizeof(array[0]))
#define MEMBER_SIZE(type, member)    sizeof(((type *)0)->member)

/***************************
 * BIT MANIPULATION MACROS *
 **************************/
// create masks
#define BIT(i)               (1 << (i))
#define BIT_COUNT(val)       (sizeof(val) << 3)
#define BIT_SET_LOW(val)     (BIT_COUNT(val) - 1 - INTRINSIC_CLZ(val))
#define BIT_SET_HIGH(val)    (BIT_COUNT(val) - 1 - INTRINSIC_CTZ(val))

#define MASK_LEN(len, low)       ((BIT(len) - 1) << (low))
#define MASK_RANGE(high, low)    MASK_LEN((high) - (low) + 1, low)
// read/write masks
#define BIT_FIELD_READ(in, mask)          (((in) & (mask)) >> BIT_SET_LOW(mask))
#define BIT_FIELD_WRITE(in, mask, val)    (((in) & ~(mask)) | ((val) << BIT_SET_LOW(mask)))

# define BYTE_SWAP32(val) INTRINSIC_BYTE_SWAP32(val)
# define BYTE_SWAP16(val) INTRINSIC_BYTE_SWAP16(val)

/********************
 * COMMON BIT MASKS *
 ********************/
 #define MASK8(i)     (MASK_RANGE(7,0) << (8 * i))
 #define MASK16(i)     (MASK_RANGE(15,0) << (16 * i))
 #define MAKS32         MASK_RANGE(31, 0)
 #define MASK_LOW8      MASK8(0)
 #define MASK_HIGH8     MASK8(1)
 #define MASK_LOW16     MASK16(0)
 #define MASK_HIGH16    MASK16(1)

#if HOST_LITTLE_ENDIAN
# define LITTLE_ENDIAN16(val)    (val)
# define LITTLE_ENDIAN32(val)    (val)
#else
# define LITTLE_ENDIAN16(val)    BYTE_SWAP16(val)
# define LITTLE_ENDIAN32(val)    BYTE_SWAP32(val)
#endif

#define LOG2_CEILING(val)  ((val) ? BIT_SET_HIGH(val) + 1 : 0)
#define LOG2_FLOOR(val)    ((val) ? BIT_SET_HIGH(val) : 0)
#define POW2_CEILING(val)  BIT(LOG2_CEILING(val))
#define POW2_FLOOR(val)    BIT(LOG2_FLOOR(val))

#define LOG2_GBYTES(n) (30 + (n))
#define LOG2_MBYTES(n) (20 + (n))
#define LOG2_KBYTES(n) (10 + (n))

#define MASK_GBYTES(n) MASK_RANGE(LOG2_GBYTES(n) - 1, 0)
#define MASK_MBYTES(n) MASK_RANGE(LOG2_MBYTES(n) - 1, 0)
#define MASK_KBYTES(n) MASK_RANGE(LOG2_KBYTES(n) - 1, 0)

#endif
