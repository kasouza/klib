#include "klib/math/vec3.h"

#include <math.h>

Vec3 klib_vec3_add(Vec3 a, Vec3 b) {
    Vec3 c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;

    return c;
}

Vec3 klib_vec3_sub(Vec3 a, Vec3 b) {
    Vec3 c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;

    return c;
}

float klib_vec3_dot(Vec3 a, Vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 klib_vec3_cross(Vec3 a, Vec3 b) {
    Vec3 c;

    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;

    return c;
}

float klib_vec3_angle(Vec3 a, Vec3 b) {
    float dot = klib_vec3_dot(a, b);
    float a_mag = klib_vec3_magnitude(a);
    float b_mag = klib_vec3_magnitude(b);

    return acos(dot / (a_mag * b_mag));
}

float klib_vec3_magnitude(Vec3 vec) {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}