#ifndef KASOUZA_KLIB_INCLUDE_MATH_VEC2_H
#define KASOUZA_KLIB_INCLUDE_MATH_VEC2_H

struct Vec2 {
    float x;
    float y;
} typedef Vec2;

Vec2 klib_vec2_add(Vec2 a, Vec2 b);
Vec2 klib_vec2_sub(Vec2 a, Vec2 b);
float klib_vec2_dot(Vec2 a, Vec2 b);

float klib_vec2_angle(Vec2 a, Vec2 b);
float klib_vec2_magnitude(Vec2 vec);

#endif