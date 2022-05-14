#include "klib/map.h"
#include "klib/vector.h"
#include <string.h>

int klib_init_map(klib_Map *map, size_t key_size, size_t value_size,
                  klib_compare_func_t compare) {
    if (!compare) {
        return 0;
    }

    if (!klib_init_vector(&map->keys, key_size)) {
        return 0;
    }

    if (!klib_init_vector(&map->values, value_size)) {
        return 0;
    }

    map->key_size = key_size;
    map->value_size = value_size;
    map->compare = compare;

    return 1;
}

int klib_free_map(klib_Map *map) {
    if (!klib_free_vector(&map->keys)) {
        return 0;
    }

    if (!klib_free_vector(&map->values)) {
        return 0;
    }

    memset(map, 0, sizeof(klib_Map));

    return 1;
}

void *klib_map_get(klib_Map *map, void *key) {
    void *value = NULL;

    for (size_t i = 0; i < map->keys.length; i++) {
        if (map->compare(klib_vector_get(&map->keys, i),
                         key) == 0) {
            value = klib_vector_get(&map->values, i);
            break;
        }
    }

    return value;
}

void *klib_map_set(klib_Map *map, void *key, void *value) {
    void *value_ptr = klib_map_get(map, key);
    if (value_ptr) {
        memcpy(value_ptr, value, map->value_size);

    } else {
        if (!klib_vector_push(&map->keys, key)) {
            return NULL;
        }

        if (!klib_vector_push(&map->values, value)) {
            return NULL;
        }
    }

    return value_ptr;
}

int klib_map_delete(klib_Map *map, void *key) {
    for (size_t i = 0; i < map->keys.length; i++) {
        if (map->compare(klib_vector_get(&map->keys, i),
                         klib_vector_get(&map->values, i)) == 0) {
            klib_vector_delete(&map->keys, i);
            klib_vector_delete(&map->values, i);
            return 1;
        }
    }

    return 0;
}
