/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum c86_error {
    GC_NO_ERROR = 0,
    GC_UNKNOWN_ERROR,
    GC_ARG_ERROR,
    GC_MALLOC_ERROR,

    GC_LAST_ERROR
} gc_error_t;

extern const char *error_desc[GC_LAST_ERROR];

#ifdef __cplusplus
}
#endif

#endif
