#include "klib/dynarr.test.h"
#include "klib/dynarr.h"
#include "klib/test.h"

KLIB_DYNARR_DECLARE(int);
KLIB_DYNARR_DEFINE(int);

bool test_dynarr() {
    KLIB_DYNARR(int) *arr = KLIB_DYNARR_CREATE(int);

    for (int i = 0; i < 128; i++) {
        KLIB_DYNARR_PUSH_BACK(arr, i * i);
    }

    for (int i = 0; i < 128; i++) {
        t_ASSERT_EQ(arr->buffer[i], i * i);
    }

    for (int i = 0; i < 128; i++) {
        arr->buffer[i] = i - 3;
    }

    for (int i = 0; i < 128; i++) {
        t_ASSERT_EQ(arr->buffer[i], i - 3);
    }

    KLIB_DYNARR_FREE(arr);

    // Test dynnar append
    KLIB_DYNARR(int) *arr2 = KLIB_DYNARR_CREATE(int);
    KLIB_DYNARR(int) *arr3 = KLIB_DYNARR_CREATE(int);

    KLIB_DYNARR_PUSH_BACK(arr2, 1);
    KLIB_DYNARR_PUSH_BACK(arr2, 2);
    KLIB_DYNARR_PUSH_BACK(arr2, 3);

    KLIB_DYNARR_PUSH_BACK(arr3, 4);
    KLIB_DYNARR_PUSH_BACK(arr3, 5);
    KLIB_DYNARR_PUSH_BACK(arr3, 6);

    KLIB_DYNARR_APPEND(arr2, arr3);

    t_ASSERT_EQ(arr2->len, 6);
    t_ASSERT_EQ(arr2->buffer[0], 1);
    t_ASSERT_EQ(arr2->buffer[1], 2);
    t_ASSERT_EQ(arr2->buffer[2], 3);
    t_ASSERT_EQ(arr2->buffer[3], 4);
    t_ASSERT_EQ(arr2->buffer[4], 5);
    t_ASSERT_EQ(arr2->buffer[5], 6);

    KLIB_DYNARR(int) *arr_empty = KLIB_DYNARR_CREATE(int);
    KLIB_DYNARR_APPEND(arr2, arr_empty);
    t_ASSERT_EQ(arr2->len, 6);

    KLIB_DYNARR_FREE(arr2);
    KLIB_DYNARR_FREE(arr3);

    return true;
}
