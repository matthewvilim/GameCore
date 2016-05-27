#ifndef LIST_H
#define LIST_H

struct list_node {
    struct list_node *prev, *next;
    char data[];
};

struct list {
    size_t size, count;
    struct list_node *head, *tail;
};

struct list_iter {
    struct list *list;
    struct list_node *node;
};

void list_init(struct list *list);
void list_head(struct list *list, struct list_iter *iter);
void list_tail(struct list *list, struct list_iter *iter);

void list_iter_next(struct list_iter *iter);
void list_iter_prev(struct list_iter *iter);
bool list_iter_valid(struct list_iter *iter);

void * list_iter_access(struct list_iter *iter);

void list_iter_append(struct list_iter *iter, struct list_node *node);
void list_iter_prepend(struct list_iter *iter, struct list_node *node);
void list_iter_remove(struct list_iter *iter);

#endif
