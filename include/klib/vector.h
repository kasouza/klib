#ifndef KASOUZA_KLIB_INCLUDE_KLIB_VECTOR_H
#define KASOUZA_KLIB_INCLUDE_KLIB_VECTOR_H

#include <stddef.h>

typedef struct klib_Vector {
    size_t capacity;
    size_t length;
    size_t type_size;
    char *buffer;
} klib_Vector;

int klib_init_vector(klib_Vector *vec, size_t type_size);
int klib_free_vector(klib_Vector *vec);

void *klib_vector_get(klib_Vector *vector, size_t index);
int klib_vector_set(klib_Vector *vector, size_t index, void *value);
int klib_vector_push(klib_Vector *vec, void *value);
int klib_vector_delete(klib_Vector *vec, size_t index);

#endif