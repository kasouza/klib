#ifndef KASOUZA_KLIB_INCLUDE_KLIB_VECTOR_H
#define KASOUZA_KLIB_INCLUDE_KLIB_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct klib_Vector {
    bool ok;
    size_t capacity;
    size_t length;
    size_t type_size;
    char *buffer;
} klib_Vector;

klib_Vector klib_create_vector(size_t type_size);
bool klib_free_vector(klib_Vector *vec);

void *klib_vector_get(klib_Vector *vector, size_t index);
bool klib_vector_set(klib_Vector *vector, size_t index, void *value);
bool klib_vector_push(klib_Vector *vec, void *value);
bool klib_vector_delete(klib_Vector *vec, size_t index);

#endif