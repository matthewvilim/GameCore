/**********************************************************************************
 *                                                                                *
 * The MIT License (MIT)                                                          *
 *                                                                                *
 * Core 8086                                                                      *
 * Copyright (c) 2014 Matthew Vilim                                               *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in all *
 * copies or substantial portions of the Software.                                *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 * SOFTWARE.                                                                      *
 *                                                                                *
 *********************************************************************************/

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
#define MASK_HIGH_B    (MASK_LOW_B << 8)
#define MASK_LOW_W     (MASK_LOW_B | MASK_HIGH_B)
 
#endif
