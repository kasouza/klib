#include "klib/container/map.h"
#include "klib/math/vec2.h"
#include "klib/math/vec3.h"
#include <klib/container/array_list.h>

#include <stdio.h>
#include <math.h>

int compare_ints(void *a, void *b) { return (*(int *)a) - (*(int *)b); }

void print(klib_Map *map, int key) {
    int res = *(int *)klib_map_get(map, &key);
    printf("%d\n", res);
}

void set(klib_Map *map, int key, int val) { klib_map_set(map, &key, &val); }

int main() {
    Vec3 vec;
    vec.x = 5;
    vec.y = 0;
    vec.z = 1;

    Vec3 vec2;
    vec2.x = 0;
    vec2.y = 5;
    vec2.z = 0;

    printf("%f\n", klib_vec3_angle(vec, vec2) * 180 / M_PI);   

    return 0;
}