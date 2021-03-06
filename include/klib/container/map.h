#ifndef KASOUZA_KLIB_INCLUDE_KLIB_CONTAINER_MAP_H
#define KASOUZA_KLIB_INCLUDE_KLIB_CONTAINER_MAP_H

#include "klib/container/array_list.h"

typedef int (*klib_compare_func_t)(const void *a, const void *b);

typedef struct klib_Map {
    size_t key_size;
    size_t value_size;

    klib_ArrayList keys;
    klib_ArrayList values;

    klib_compare_func_t compare;
    bool ok;
} klib_Map;

klib_Map klib_create_map(size_t key_size, size_t value_size,
                             klib_compare_func_t compare);
bool klib_free_map(klib_Map *map);

void *klib_map_get(klib_Map *map, void *key);
bool klib_map_set(klib_Map *map, void *key, void *value);
bool klib_map_delete(klib_Map *map, void *key);

#endif