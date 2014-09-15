/********************************************************************************
 *
 * The MIT License (MIT)
 *
 * Core 8086
 * Copyright (c) 2014 Matthew Vilim
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef C86_CONFIG_H
#define C86_CONFIG_H

// native architecture endianness
#ifdef __BIG_ENDIAN__
# define C86_ARCH_NATIVE_BIG_ENDIAN     __BIG_ENDIAN__
# define C86_ARCH_NATIVE_LITTLE_ENDIAN !__BIG_ENDIAN__
#elif defined __LITTLE_ENDIAN__
# define C86_ARCH_NATIVE_LITTLE_ENDIAN  __LITTLE_ENDIAN__
# define C86_ARCH_NATIVE_BIG_ENDIAN    !__LITTLE_ENDIAN__
#else
# error native architecture endianness must be defined
#endif

#if __has_attribute(always_inline)
# define C86_INLINE static inline __attribute__((always_inline))
#else
# warn functions will not be force inlined
# define C86_INLINE static inline
#endif

#endif
