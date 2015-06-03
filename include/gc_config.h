/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef GC_CONFIG_H
#define GC_CONFIG_H

// native architecture endianness
#ifdef __BIG_ENDIAN__
# define GC_ARCH_NATIVE_BIG_ENDIAN     __BIG_ENDIAN__
#else
# error native architecture endianness must be defined
#endif

#if __has_attribute(always_inline)
# define GC_INLINE static inline __attribute__((always_inline))
#else
# warn functions will not be force inlined
# define GC_INLINE static inline
#endif

#endif
