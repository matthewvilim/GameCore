/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/compiler.h
 */

#ifndef __has_builtin
# define __has_builtin(feature) 0
#endif

#if __has_builtin(__builtin_bswap32)
# define INTRINSIC_BYTE_SWAP32(val) __builtin_bswap32(val)
#else
# warn instrinc byte swap 32 undefined
#endif

#if __has_builtin(__builtin_bswap16)
# define INTRINSIC_BYTE_SWAP16(val) __builtin_bswap16(val)
#else
# warn instrinc byte swap 16 undefined
#endif

#if __has_builtin(__builtin_clz)
# define INTRINSIC_CLZ(val) __builtin_clz(val)
#else
# error low bit instrinsic must be defined
#endif

#if __has_builtin(__builtin_ctz)
# define INTRINSIC_CTZ(val) __builtin_ctz(val)
#else
# error low bit instrinsic must be defined
#endif

#ifdef __LITTLE_ENDIAN__
# define HOST_LITTLE_ENDIAN     __LITTLE_ENDIAN__
#else
# error host endianness must be defined
#endif

#if __has_attribute(always_inline)
# define INLINE_FORCE inline __attribute__((always_inline))
#else
# warn functions might not be inlined
# define INLINE_FORCE inline
#endif

#if __has_attribute(__builtin_expect)
#define BRANCH_LIKELY(cond)       __builtin_expect((cond), 1)
#define BRANCH_UNLIKELY(cond)     __builtin_expect((cond), 0)
#else
#define BRANCH_LIKELY(cond)
#define BRANCH_UNLIKELY(cond)
#endif
