#ifndef KASOUZA_KLIB_INCLUDE_MATH_VEC3_H
#define KASOUZA_KLIB_INCLUDE_MATH_VEC3_H

struct Vec3 {
    float x;
    float y;
    float z;
} typedef Vec3;

Vec3 klib_vec3_add(Vec3 a, Vec3 b);
Vec3 klib_vec3_sub(Vec3 a, Vec3 b);
float klib_vec3_dot(Vec3 a, Vec3 b);
Vec3 klib_vec3_cross(Vec3 a, Vec3 b);

float klib_vec3_angle(Vec3 a, Vec3 b);
float klib_vec3_magnitude(Vec3 vec);

#endif