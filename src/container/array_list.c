#include "klib/container/array_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_INITIAL_CAPACITY 4
#define ARRAY_SCALE_FACTOR 2

void grow(klib_ArrayList *arr) {
    size_t new_capacity = arr->capacity * ARRAY_SCALE_FACTOR;
    arr->buffer = reallocarray(arr->buffer, new_capacity, arr->type_size);
    arr->capacity = new_capacity;
}

klib_ArrayList klib_create_array_list(size_t type_size) {
    klib_ArrayList arr;
    memset(&arr, 0, sizeof(arr));

    arr.buffer = malloc(type_size * ARRAY_INITIAL_CAPACITY);

    if (arr.buffer) {
        arr.capacity = ARRAY_INITIAL_CAPACITY;
        arr.length = 0;
        arr.type_size = type_size;
        arr.ok = true;
    }

    return arr;
}

bool klib_free_array_list(klib_ArrayList *arr) {
    if (!arr->buffer || arr->capacity == 0) {
        return false;
    }

    free(arr->buffer);
    memset(arr, 0, sizeof(klib_ArrayList));

    return true;
}

void *klib_array_list_get(klib_ArrayList *arr, size_t index) {
    if (!arr->buffer || arr->length == 0) {
        printf("cuceta\n");
        return NULL;
    }

    // Index out of bounds
    if (index >= arr->length) {
        return NULL;
    }

    return arr->buffer + (index * arr->type_size);
}

bool klib_array_list_set(klib_ArrayList *arr, size_t index, void *value) {
    // Can't set if there's no space or index is out of bounds
    if (!arr->buffer || arr->capacity == 0) {
        return false;
    }

    // Index out of bounds
    if (index >= arr->length) {
        return false;
    }

    memcpy(arr->buffer + (index * arr->type_size), value,
           arr->type_size);

    return true;
}

bool klib_array_list_push(klib_ArrayList *arr, void *value) {
    // Can't push if there's no space or index is out of bounds
    if (!arr->buffer || arr->capacity == 0) {
        return false;
    }

    // Grow the array if there's no space to add a new element
    if (arr->length >= arr->capacity) {
        grow(arr);
    }

    arr->length++;
    return klib_array_list_set(arr, arr->length - 1, value);
}

bool klib_array_list_delete(klib_ArrayList *arr, size_t index) {
    // Can't set if there's no space or index is out of bounds
    if (!arr->buffer || arr->capacity == 0) {
        return false;
    }

    // Index out of bounds
    if (index >= arr->length) {
        return false;
    }

    // Create new buffer with the same capacity
    size_t new_length = arr->length - 1;
    void *new_buffer = malloc(arr->capacity * arr->type_size);
    if (!new_buffer) {
        return false;
    }

    // Copy the data from the old buffer to the new, except for the removed
    // element
    memcpy(new_buffer, arr->buffer, index * arr->type_size);
    memcpy(new_buffer + (index * arr->type_size),
           arr->buffer + ((index + 1) * arr->type_size),
           (arr->length - index - 1) * arr->type_size);

    // Free old buffer
    free(arr->buffer);

    // Update the array
    arr->buffer = new_buffer;
    arr->length = new_length;

    return true;
}
