#include "klib/math/vec4.h"

#include <math.h>

Vec4 klib_vec4_add(Vec4 a, Vec4 b) {
    Vec4 c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    c.w = a.w + b.w;

    return c;
}

Vec4 klib_vec4_sub(Vec4 a, Vec4 b) {
    Vec4 c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    c.w = a.w - b.w;

    return c;
}

float klib_vec4_dot(Vec4 a, Vec4 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

float klib_vec4_angle(Vec4 a, Vec4 b) {
    float dot = klib_vec4_dot(a, b);
    float a_mag = klib_vec4_magnitude(a);
    float b_mag = klib_vec4_magnitude(b);

    return acos(dot / (a_mag * b_mag));
}

float klib_vec4_magnitude(Vec4 vec) {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) +
                (vec.w * vec.w));
}