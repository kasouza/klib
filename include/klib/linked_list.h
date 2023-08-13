#ifndef KASOUZA_KLIB_INCLUDE_KLIB_INCLUDE_KLIB_LINKED_LIST_H
#define KASOUZA_KLIB_INCLUDE_KLIB_INCLUDE_KLIB_LINKED_LIST_H

#include <stddef.h>

#define KLIB_LINKED_LIST_PUSH_FRONT(list, type, value)                         \
    {                                                                          \
        type __temp_value__ = value;                                           \
        KLIB_linked_list_push_front((list), &__temp_value__,                   \
                                    sizeof(__temp_value__));                   \
    }

#define KLIB_LINKED_LIST_PUSH_BACK(list, type, value)                         \
    {                                                                          \
        type __temp_value__ = value;                                           \
        KLIB_linked_list_push_back((list), &__temp_value__,                   \
                                    sizeof(__temp_value__));                   \
    }

struct KLIB_LinkedListNode {
    void *data;
    struct KLIB_LinkedListNode *next;
    struct KLIB_LinkedListNode *previous;
};

struct KLIB_LinkedList {
    struct KLIB_LinkedListNode *head;
    struct KLIB_LinkedListNode *tail;
    size_t length;
};

struct KLIB_LinkedList *KLIB_create_linked_list();

void KLIB_linked_list_push_front(struct KLIB_LinkedList *list, void *data,
                                 size_t data_size);

void KLIB_linked_list_custom_push_front(
    struct KLIB_LinkedList *list, void *data, size_t data_size,
    void *(*copy_function)(void *restrict dest, const void *restrict src,
                           size_t size));

void KLIB_linked_list_push_back(struct KLIB_LinkedList *list, void *data,
                                      size_t data_size);

void KLIB_linked_list_custom_push_back(
    struct KLIB_LinkedList *list, void *data, size_t data_size,
    void *(*copy_function)(void *restrict dest, const void *restrict src,
                           size_t size));

void *KLIB_linked_list_at(struct KLIB_LinkedList *list, int n);

void KLIB_linked_list_remove(struct KLIB_LinkedList *list, int n);
void KLIB_linked_list_custom_remove(struct KLIB_LinkedList *list, int n, void (*free_function)(void *));

void* KLIB_linked_list_pop_front(struct KLIB_LinkedList *list);
void* KLIB_linked_list_pop_back(struct KLIB_LinkedList *list);

void KLIB_free_linked_list(struct KLIB_LinkedList *list);

void KLIB_free_custom_linked_list(struct KLIB_LinkedList *list,
                                  void (*free_function)(void *));

#endif
