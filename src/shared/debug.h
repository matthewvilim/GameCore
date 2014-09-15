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

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

/***********
 * LOGGING *
 ***********/

#define LOG_PREFIX "C86: "

#define LOG(msg, ...)                                         \
    do {                                                      \
        printf("%s" msg "\n", LOG_PREFIX, ##__VA_ARGS__) \
    } while(0);

#define LOG_STDERR(level, msg, ...)                                                                                        \
    do {                                                                                                                   \
        fprintf(stderr, "%s[%s] (%s - %s:%d) - " msg "\n", LOG_PREFIX, level, __func__, __FILE__, __LINE__, ##__VA_ARGS__) \
    } while(0);

#define INFO(msg, ...)     LOG_STDERR("INFO", msg, ##__VA_ARGS__)
#define WARN(msg, ...)     LOG_STDERR("WARN", msg, ##__VA_ARGS__)
#define ERROR(msg, ...)    LOG_STDERR("ERROR", msg, ##__VA_ARGS__)

#define ERROR_DESC(error, msg, ...)    ERROR("%s: " msg, error_desc[error], ##__VA_ARGS__)

#if C86_DEBUG
# define DBG_INFO(msg, ...)     INFO(msg, ...)
# define DBG_WARN(msg, ...)     WARN(msg, ...)
# define DBG_ERROR(msg, ...)    ERROR(msg, ...)
#else
# define DBG_INFO(msg, ...)
# define DBG_WARN(msg, ...)
# define DBG_ERROR(msg, ...)
#endif // C86_DEBUG

/**********
 * ASSERT *
 **********/

#define ASSERT(cond, msg, ...)                      \
    do {                                            \
        if (!(cond)) {                              \
            LOG_STDERR("ABORT", msg, ##__VA_ARGS__) \
            abort();                                \
        }                                           \
    } while(0);

#endif
