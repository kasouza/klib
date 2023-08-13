#include "klib/linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct KLIB_LinkedList *KLIB_create_linked_list() {
    struct KLIB_LinkedList *linked_list =
        calloc(1, sizeof(struct KLIB_LinkedList));
    return linked_list;
}

struct KLIB_LinkedListNode *create_linked_list_node(size_t data_size) {
    struct KLIB_LinkedListNode *node =
        malloc(sizeof(struct KLIB_LinkedListNode));
    if (!node) {
        fprintf(stderr,
                "ERROR: Could not allocate memory for linked list node.\n");
        return NULL;
    }

    node->next = NULL;
    node->previous = NULL;
    node->data = calloc(1, data_size);

    if (!node->data) {
        free(node);

        fprintf(stderr,
                "ERROR: Could not allocate memory for linked list node.\n");
        return NULL;
    }

    return node;
}

void KLIB_linked_list_push_front(struct KLIB_LinkedList *list, void *data,
                                 size_t data_size) {
    KLIB_linked_list_custom_push_front(list, data, data_size, memcpy);
}

void KLIB_linked_list_custom_push_front(
    struct KLIB_LinkedList *list, void *data, size_t data_size,
    void* (*copy_function)(void *restrict dest, const void *restrict src,
                          size_t size)) {
    assert(list != NULL);

    struct KLIB_LinkedListNode *next = list->head;

    list->head = create_linked_list_node(data_size);
    if (!list->head) {
        list->head = next;
        return;
    }

    copy_function(list->head->data, data, data_size);

    list->head->next = next;
    
    if (next) {
        next->previous = list->head;
    } else {
        list->tail = list->head;
    }

    list->length++;
}

void KLIB_linked_list_push_back(struct KLIB_LinkedList *list, void *data,
                                 size_t data_size) {
    KLIB_linked_list_custom_push_back(list, data, data_size, memcpy);
}

void KLIB_linked_list_custom_push_back(
    struct KLIB_LinkedList *list, void *data, size_t data_size,
    void* (*copy_function)(void *restrict dest, const void *restrict src,
                          size_t size)) {
    assert(list != NULL);

    struct KLIB_LinkedListNode *previous = list->tail;

    list->tail = create_linked_list_node(data_size);
    if (!list->tail) {
        list->head = previous;
        return;
    }

    copy_function(list->tail->data, data, data_size);

    list->tail->previous = previous;
    
    if (previous) {
        previous->next = list->tail;
    } else {
        list->head = list->tail;
    }

    list->length++;
}

void *KLIB_linked_list_at(struct KLIB_LinkedList *list, int n) {
    assert(list != NULL);

    size_t idx = 0;
    if (n >= 0) {
        idx = n;
    } else {
        idx = n + list->length;
    }

    assert(idx >= 0 && idx < list->length && "index out of bounds");

    if (idx == 0) {
        return list->head->data;
    }

    if (idx == list->length - 1) {
        return list->tail->data;
    }

    struct KLIB_LinkedListNode* current;
    int order;
    size_t current_idx;

    if (idx > (list->length / 2)) {
        current = list->tail;
        order = -1;
        current_idx = list->length - 1;

    } else {
        current = list->head;
        order = 1;
        current_idx = 0;
    }

    while (current != NULL) {
        struct KLIB_LinkedListNode *next = order > 0 ? current->next : current->previous;

        if (current_idx == idx) {
            return current->data;
        }

        current_idx += order;
        current = next;
    }

    return NULL;
}

void KLIB_linked_list_remove(struct KLIB_LinkedList *list, int n) {
    KLIB_linked_list_custom_remove(list, n, free);
}

void KLIB_linked_list_custom_remove(struct KLIB_LinkedList *list, int n, void (*free_function)(void *)) {
    assert(list != NULL);

    size_t idx = 0;
    if (n >= 0) {
        idx = n;
    } else {
        idx = n + list->length;
    }

    assert(idx >= 0 && idx < list->length && "index out of bounds");

    if (idx == 0) {
        struct KLIB_LinkedListNode *next = list->head->next;
        if (list->head->data != NULL) {
            free_function(list->head->data);
            list->head->data = NULL;
        }

        free(list->head);
        list->head = next;
        if (list->head != NULL) {
            list->head->previous = NULL;
        }

        list->length--;

        return;
    }

    if (idx == list->length - 1) {
        struct KLIB_LinkedListNode *previous = list->tail->previous;
        if (list->tail->data != NULL) {
            free_function(list->tail->data);
            list->tail->data = NULL;
        }

        free(list->tail);
        list->tail = previous;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }

        list->length--;

        return;
    }

    struct KLIB_LinkedListNode* current;
    int order;
    size_t current_idx;

    if (idx > (list->length / 2)) {
        current = list->tail;
        order = -1;
        current_idx = list->length - 1;

    } else {
        current = list->head;
        order = 1;
        current_idx = 0;
    }

    while (current != NULL) {
        struct KLIB_LinkedListNode *next = order > 0 ? current->next : current->previous;

        if (current_idx == idx) {
            struct KLIB_LinkedListNode *previous = current->previous;
            struct KLIB_LinkedListNode *next = current->next;

            if (current->data != NULL) {
                free_function(current->data);
                current->data = NULL;
            }

            free(current);

            if (previous != NULL) {
                previous->next = next;
            } else if (list->head != NULL) {
                list->head = next;
            }

            if (next != NULL) {
                next->previous = previous;
            } else if (list->tail != NULL) {
                list->tail = previous;
            }

            list->length--;

            return;
        }

        current_idx += order;
        current = next;
    }
}

void* KLIB_linked_list_pop_front(struct KLIB_LinkedList *list) {
    if (list->head == NULL) {
        return NULL;
    }

    void* data = list->head->data;
    list->head->data = NULL;

    KLIB_linked_list_remove(list, 0);

    return data;
}

void* KLIB_linked_list_pop_back(struct KLIB_LinkedList *list) {
    if (list->tail == NULL) {
        return NULL;
    }

    void* data = list->tail->data;
    list->tail->data = NULL;

    KLIB_linked_list_remove(list, -1);

    return data;
}

void KLIB_free_linked_list(struct KLIB_LinkedList *list) {
    KLIB_free_custom_linked_list(list, free);
}

void KLIB_free_custom_linked_list(struct KLIB_LinkedList *list,
                                  void (*free_function)(void *)) {
    assert(list != NULL);

    if (list->length > 0) {
        while (list->head != NULL) {
            struct KLIB_LinkedListNode *next = list->head->next;

            if (list->head->data != NULL) {
                free_function(list->head->data);
                list->head->data = NULL;
            }

            free(list->head);
            list->head = next;
        }
    }

    list->length = 0;

    free(list);
    list = NULL;
}
