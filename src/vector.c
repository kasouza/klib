#include "klib/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_INITIAL_CAPACITY 4
#define ARRAY_SCALE_FACTOR 2

void grow(klib_Vector *arr) {
    size_t new_capacity = arr->capacity * ARRAY_SCALE_FACTOR;
    arr->buffer = reallocarray(arr->buffer, new_capacity, arr->type_size);
    arr->capacity = new_capacity;
}

klib_Vector klib_create_vector(size_t type_size) {
    klib_Vector vec;
    memset(&vec, 0, sizeof(vec));

    vec.buffer = malloc(type_size * ARRAY_INITIAL_CAPACITY);

    if (vec.buffer) {
        vec.capacity = ARRAY_INITIAL_CAPACITY;
        vec.length = 0;
        vec.type_size = type_size;
        vec.ok = true;
    }

    return vec;
}

bool klib_free_vector(klib_Vector *vec) {
    if (!vec->buffer || vec->capacity == 0) {
        return false;
    }

    free(vec->buffer);
    memset(vec, 0, sizeof(klib_Vector));

    return true;
}

void *klib_vector_get(klib_Vector *vector, size_t index) {
    if (!vector->buffer || vector->length == 0) {
        printf("cuceta\n");
        return NULL;
    }

    // Index out of bounds
    if (index >= vector->length) {
        return NULL;
    }

    return vector->buffer + (index * vector->type_size);
}

bool klib_vector_set(klib_Vector *vector, size_t index, void *value) {
    // Can't set if there's no space or index is out of bounds
    if (!vector->buffer || vector->capacity == 0) {
        return false;
    }

    // Index out of bounds
    if (index >= vector->length) {
        return false;
    }

    memcpy(vector->buffer + (index * vector->type_size), value,
           vector->type_size);

    return true;
}

bool klib_vector_push(klib_Vector *vec, void *value) {
    // Can't push if there's no space or index is out of bounds
    if (!vec->buffer || vec->capacity == 0) {
        return false;
    }

    // Grow the array if there's no space to add a new element
    if (vec->length >= vec->capacity) {
        grow(vec);
    }

    vec->length++;
    return klib_vector_set(vec, vec->length - 1, value);
}

bool klib_vector_delete(klib_Vector *vec, size_t index) {
    // Can't set if there's no space or index is out of bounds
    if (!vec->buffer || vec->capacity == 0) {
        return false;
    }

    // Index out of bounds
    if (index >= vec->length) {
        return false;
    }

    // Create new buffer with the same capacity
    size_t new_length = vec->length - 1;
    void *new_buffer = malloc(vec->capacity * vec->type_size);
    if (!new_buffer) {
        return false;
    }

    // Copy the data from the old buffer to the new, except for the removed
    // element
    memcpy(new_buffer, vec->buffer, index * vec->type_size);
    memcpy(new_buffer + (index * vec->type_size),
           vec->buffer + ((index + 1) * vec->type_size),
           (vec->length - index - 1) * vec->type_size);

    // Free old buffer
    free(vec->buffer);

    // Update the array
    vec->buffer = new_buffer;
    vec->length = new_length;

    return true;
}
