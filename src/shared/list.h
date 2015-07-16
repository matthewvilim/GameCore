/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/list.h
 */

#ifndef MACROS_H
#define MACROS_H

#define LIST_STRUCT(type)        \
    struct {                     \
        struct type *next, prev; \
    }

#define LIST_INIT(list)      \
    do {                     \
        (list)->next = NULL; \
        (list)->prev = NULL; \
    } while(0);

#define LIST_FOREACH(var, list) (for (var) = list; (var); (var) = (var)->next)

#define LIST_INSERT(list, entry)      \
    (entry)->next = list;             \
    if (list) {                       \
        (entry)->prev = (list)->prev; \
        (list)->prev = entry;         \
    }

#define LIST_REMOVE(entry)                   \
    if ((entry)->prev) {                     \
        (entry)->prev->next = (entry)->next; \
    }                                        \
    if ((entry)->next) {                     \
        (entry)->next->prev = (entry)->prev; \
    }

#define

#endif
