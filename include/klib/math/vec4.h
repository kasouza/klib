#ifndef KASOUZA_KLIB_INCLUDE_MATH_VEC4_H
#define KASOUZA_KLIB_INCLUDE_MATH_VEC4_H

struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} typedef Vec4;

Vec4 klib_vec4_sub(Vec4 a, Vec4 b);
Vec4 klib_vec4_add(Vec4 a, Vec4 b);
float klib_vec4_dot(Vec4 a, Vec4 b);
Vec4 klib_vec4_cross(Vec4 a, Vec4 b);

float klib_vec4_angle(Vec4 a, Vec4 b);
float klib_vec4_magnitude(Vec4 vec);

#endif