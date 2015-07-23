/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/compiler.h
 */

#ifndef __has_builtin
# define __has_builtin(expr) 0
#endif

#ifdef __BIG_ENDIAN__
# define ARCH_NATIVE_BIG_ENDIAN     __BIG_ENDIAN__
#else
# error native architecture endianness must be defined
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
