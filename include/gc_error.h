/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef GC_ERROR_H
#define GC_ERROR_H

typedef enum c86_error {
    GC_NO_ERROR = 0,
    GC_UNKNOWN_ERROR,
    GC_ARG_ERROR,
    GC_MALLOC_ERROR,
    
    GC_LAST_ERROR
} gc_error_t;

extern const char *error_desc[GC_LAST_ERROR];

#endif