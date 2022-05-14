#include "klib/map.h"
#include "klib/vector.h"
#include <string.h>

klib_Map klib_create_map(size_t key_size, size_t value_size,
                             klib_compare_func_t compare) {
    klib_Map map;
    memset(&map, 0, sizeof(map));

    if (!compare) {
        return map;
    }

    map.keys = klib_create_vector(key_size);
    if (!map.keys.ok) {
        return map;
    }

    map.values = klib_create_vector(value_size);
    if (!map.values.ok) {
        klib_free_vector(&map.keys);
        return map;
    }

    map.compare = compare;
    map.key_size = key_size;
    map.value_size = value_size;
    map.ok = true;

    return map;
}

bool klib_free_map(klib_Map *map) {
    if (!klib_free_vector(&map->keys)) {
        return false;
    }

    if (!klib_free_vector(&map->values)) {
        return false;
    }

    memset(map, 0, sizeof(klib_Map));

    return true;
}

void *klib_map_get(klib_Map *map, void *key) {
    void *value = NULL;

    for (size_t i = 0; i < map->keys.length; i++) {
        if (map->compare(klib_vector_get(&map->keys, i), key) == 0) {
            value = klib_vector_get(&map->values, i);
            break;
        }
    }

    return value;
}

bool klib_map_set(klib_Map *map, void *key, void *value) {
    void *value_ptr = klib_map_get(map, key);
    if (value_ptr) {
        memcpy(value_ptr, value, map->value_size);

    } else {
        if (!klib_vector_push(&map->keys, key) ||
            !klib_vector_push(&map->values, value)) {
            return false;
        }
    }

    return true;
}

bool klib_map_delete(klib_Map *map, void *key) {
    for (size_t i = 0; i < map->keys.length; i++) {
        if (map->compare(klib_vector_get(&map->keys, i),
                         klib_vector_get(&map->values, i)) == 0) {
            klib_vector_delete(&map->keys, i);
            klib_vector_delete(&map->values, i);
            return true;
        }
    }

    return false;
}
