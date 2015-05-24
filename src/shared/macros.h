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
#define MASK_GET_VAL(in, mask)         (((in) & (mask)) >> LOW_BIT_IDX(mask))
#define MASK_SET_VAL(in, mask, val)    (((in) & ~(mask)) | ((val) << LOW_BIT_IDX(mask)))
#define MASK_CLEAR(in, mask)           MASK_SET_VAL(in, mask, 0)
#define MASK_TEST_VAL(in, mask, val)   (MASK_SET_VAL(0, mask, (val)) == ((in) & (mask)))
// boolean operations
#define MASK_OR_VAL(in, mask, val)     (MASK_SET_VAL(0, mask, (val)) | (in))
#define MASK_AND_VAL(in, mask, val)    (MASK_SET_VAL(0, mask, (val)) & (in))
#define MASK_XOR_VAL(in, mask, val)    (MASK_SET_VAL(0, mask, (val)) ^ (in))

/********************
 * COMMON BIT MASKS *
 ********************/

#define MASK_LOW_B     MASK_RANGE(8, 0)
#define MASK_HIGH_B   (MASK_LOW_B << 8)
#define MASK_W        (MASK_LOW_B | MASK_HIGH_B)

#endif
