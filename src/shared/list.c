#include "list.h"

void
list_init(struct list *list) {
    list->count = 0;
    list->head = list->tail = NULL;
}

void
list_head(struct list *list, struct list_iter *iter) {
    iter->list = list;
    iter->node = list->head;
}

void
list_tail(struct list *list, struct list_iter *iter) {
    iter->list = list;
    iter->node = list->tail;
}

void
list_iter_append(struct list_iterator *iterator, struct list_node *node) {
    node->prev = iterator->node;
    node->next = iterator->node->next;

    iterator->node->next = node;
    iterator->list->count++;
    iterator->node = node;
}

void
list_iter_prepend(struct list_iterator *iterator, struct list_node *node) {
    node->prev = iterator->node->prev;
    node->next = iterator->node;

    iterator->node->prev = node;
    iterator->list->count++;
    iterator->node = node;
}

void
list_iter_remove(struct list_iterator *iterator) {
    iterator->node->prev->next = iterator->node->next;
    iterator->node->next->prev = iterator->node->prev;
    iterator->list->count--;
}

void
list_iter_next(struct list_iterator *iterator) {
    iterator->node = iterator->node->next;
}

void
list_iter_prev(struct list_iterator *iterator) {
    iterator->node = iterator->node->prev;
}

bool
list_iter_valid(struct list_iter *iter) {
    return !!iter->node;
}

void *
list_iterator_access(struct list_iterator *iterator) {
    return &iterator->node->data;
}
