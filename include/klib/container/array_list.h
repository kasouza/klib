#ifndef KASOUZA_KLIB_INCLUDE_KLIB_CONTAINER_ARRAY_LIST_H
#define KASOUZA_KLIB_INCLUDE_KLIB_CONTAINER_ARRAY_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct klib_ArrayList {
    bool ok;
    size_t capacity;
    size_t length;
    size_t type_size;
    char *buffer;
} klib_ArrayList;

klib_ArrayList klib_create_array_list(size_t type_size);
bool klib_free_array_list(klib_ArrayList *vec);

void *klib_array_list_get(klib_ArrayList *arr, size_t index);
bool klib_array_list_set(klib_ArrayList *arr, size_t index, void *value);
bool klib_array_list_push(klib_ArrayList *arr, void *value);
bool klib_array_list_delete(klib_ArrayList *arr, size_t index);

#endif