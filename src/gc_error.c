/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <gc_error.h>

static const char *error_desc[GC_LAST_ERROR] = {
    "No error",
    "Unknown error",
    "Invalid argument",
    "Memory allocation failure"
}
