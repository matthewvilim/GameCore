/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/debug.h
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

/***********
 * LOGGING *
 ***********/

#define LOG_PREFIX "C86: "

#define LOG(msg, ...)                                    \
    do {                                                 \
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

#if GC_DEBUG
# define DBG_INFO(msg, ...)     INFO(msg, ...)
# define DBG_WARN(msg, ...)     WARN(msg, ...)
# define DBG_ERROR(msg, ...)    ERROR(msg, ...)
#else
# define DBG_INFO(msg, ...)
# define DBG_WARN(msg, ...)
# define DBG_ERROR(msg, ...)
#endif // GC_DEBUG

/**********
 * ASSERT *
 **********/

#if DEBUG
# define ASSERT(cond, msg, ...)                      \
    do {                                            \
        if (!(cond)) {                              \
            ERROR("assertion: " #cond, msg, ##__VA_ARGS__) \
            abort();                                \
        }                                           \
    } while(0);
#else
# define ASSERT(cond, msg, ...)
#endif

#endif
