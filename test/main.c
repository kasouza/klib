#include "klib/map.h"
#include <klib/vector.h>

#include <stdio.h>

int compare_ints(void *a, void *b) { return (*(int *)a) - (*(int *)b); }

void print(klib_Map *map, int key) {
    int res = *(int *)klib_map_get(map, &key);
    printf("%d\n", res);
}

void set(klib_Map *map, int key, int val) { klib_map_set(map, &key, &val); }

int main() {
    klib_Map map;
    klib_init_map(&map, sizeof(int), sizeof(int), compare_ints);

    set(&map, 3, 32);
    set(&map, 4, 85);
    set(&map, 5, 54);

    print(&map, 3);
    print(&map, 4);
    print(&map, 5);

    klib_free_map(&map);

    return 0;
}