#include "klib/math/vec2.h"

#include <math.h>

Vec2 klib_vec2_add(Vec2 a, Vec2 b) {
    Vec2 vec;

    vec.x = a.x + b.x;
    vec.y = a.y + b.y;

    return vec;
}

Vec2 klib_vec2_sub(Vec2 a, Vec2 b) {
    Vec2 vec;

    vec.x = a.x - b.x;
    vec.y = a.y - b.y;

    return vec;
}

float klib_vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

float klib_vec2_angle(Vec2 a, Vec2 b) {
    float dot = klib_vec2_dot(a, b);
    float a_mag = klib_vec2_magnitude(a);
    float b_mag = klib_vec2_magnitude(b);

    return acos(dot / (a_mag * b_mag));
}


float klib_vec2_magnitude(Vec2 vec) {
    return sqrt((vec.x * vec.x) +  (vec.y * vec.y));
}

