#include "klib/hash_map.test.h"
#include "klib/hash_map.h"
#include "klib/test.h"

#include <stddef.h>

size_t hash_int(void *a, size_t capacity) {
    assert(a != NULL);
    return *(int *)a % capacity;
}

int compare_int(void *a, void *b) {
    assert(a != NULL);
    assert(b != NULL);

    return *(int *)a - *(int *)b;
}

KLIB_HASH_MAP_DECLARE(int, int);
KLIB_HASH_MAP_DEFINE(int, int, hash_int, compare_int);

bool test_hash_map_bucket() {
    // Test create bucket
    KLIB_HASH_MAP_BUCKET(int, int) *bucket =
        KLIB_HASH_MAP_BUCKET_CREATE(int, int, compare_int);
    t_ASSERT(bucket != NULL);

    t_ASSERT_EQ(bucket->compare_func, compare_int);
    t_ASSERT_EQ(bucket->nodes_cap, KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP);
    t_ASSERT_EQ(bucket->nodes_len, 0);
    t_ASSERT(bucket->nodes != NULL);

    // Test setting
    for (int i = 0; i < KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP - 1; i++) {
        int key = i;
        int value = i * 99;

        KLIB_HASH_MAP_BUCKET_SET(int, int, bucket, key, value);
        t_ASSERT_EQ(bucket->nodes_len, i + 1);
        t_ASSERT_EQ(bucket->nodes_cap, KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP);
        t_ASSERT_EQ(bucket->nodes[i].key, key);
        t_ASSERT_EQ(bucket->nodes[i].value, value);
    }

    // Set the same keys again, should change only the values
    int len = bucket->nodes_len;

    for (int i = 0; i < KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP - 1; i++) {
        int key = i;
        int value = i * 55;

        KLIB_HASH_MAP_BUCKET_SET(int, int, bucket, key, value);
        t_ASSERT_EQ(bucket->nodes_len, len);
        t_ASSERT_EQ(bucket->nodes_cap, KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP);
        t_ASSERT_EQ(bucket->nodes[i].key, key);
        t_ASSERT_EQ(bucket->nodes[i].value, value);

        int *returned = KLIB_HASH_MAP_BUCKET_GET(int, int, bucket, key);
        t_ASSERT_NOT_NULL(returned);
        t_ASSERT_EQ(*returned, value);
    }

    // Set new keys, should grow
    int new_cap = KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP *
                  KLIB_HASH_MAP_BUCKET_NODES_GROWTH_FACTOR;

    for (int i = 0; i < KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP; i++) {
        int key = (i + 1) * 99;
        int value = i * 55;

        KLIB_HASH_MAP_BUCKET_SET(int, int, bucket, key, value);
        t_ASSERT_EQ(bucket->nodes_len, len + i + 1);
        t_ASSERT_EQ(bucket->nodes_cap, new_cap);

        t_ASSERT_EQ(bucket->nodes[len + i].key, key);
        t_ASSERT_EQ(bucket->nodes[len + i].value, value);

        int *returned = KLIB_HASH_MAP_BUCKET_GET(int, int, bucket, key);
        t_ASSERT_NOT_NULL(returned);
        t_ASSERT_EQ(*returned, value);
    }

    KLIB_HASH_MAP_BUCKET_SET(int, int, bucket, 31231, 312312321);
    t_ASSERT_EQ(bucket->nodes_cap,
                new_cap * KLIB_HASH_MAP_BUCKET_NODES_GROWTH_FACTOR);

    // Assert that the values and key have not been messed up by the growth
    for (int i = 0; i < KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP - 1; i++) {
        int key = i;
        int value = i * 55;

        t_ASSERT_EQ(bucket->nodes[i].key, key);
        t_ASSERT_EQ(bucket->nodes[i].value, value);

        int *returned = KLIB_HASH_MAP_BUCKET_GET(int, int, bucket, key);
        t_ASSERT_NOT_NULL(returned);
        t_ASSERT_EQ(*returned, value);
    }

    for (int i = 0; i < KLIB_HASH_MAP_BUCKET_NODES_INITIAL_CAP; i++) {
        int key = (i + 1) * 99;
        int value = i * 55;

        t_ASSERT_EQ(bucket->nodes[len + i].key, key);
        t_ASSERT_EQ(bucket->nodes[len + i].value, value);

        int *returned = KLIB_HASH_MAP_BUCKET_GET(int, int, bucket, key);
        t_ASSERT_NOT_NULL(returned);
        t_ASSERT_EQ(*returned, value);
    }

    // Try to get some other keys, must return null
    for (int i = 999999; i < 999999 + 100; i++) {
        int *returned = KLIB_HASH_MAP_BUCKET_GET(int, int, bucket, i);
        t_ASSERT_NULL(returned);
    }

    KLIB_HASH_MAP_BUCKET_FREE(int, int, bucket);
    bucket = NULL;

    return true;
}

bool test_hash_map() {
    KLIB_HASH_MAP(int, int) *map = KLIB_HASH_MAP_CREATE(int, int);

    int key = 32;
    int value = 42;
    KLIB_HASH_MAP_SET(int, int, map, key, value);

    int hash = hash_int(&key, map->buckets_cap);
    t_ASSERT_EQ(map->buckets[hash]->nodes[0].value, value);

    int *got = KLIB_HASH_MAP_GET(int, int, map, key);
    t_ASSERT(got != NULL);
    t_ASSERT_EQ(*got, value);

    t_ASSERT_NULL(KLIB_HASH_MAP_GET(int, int, map, 3123));

    KLIB_HASH_MAP_FREE(int, int, map);
    map = NULL;

    // Test
    map = KLIB_HASH_MAP_CREATE(int, int);

    // Add new values an32000d check if they are set correctly
    int num_iter = 16000;
    for (int i = 0; i < num_iter; i++) {
        int key = i;
        int value = i * 99;

        KLIB_HASH_MAP_SET(int, int, map, key, value);

        int *got = KLIB_HASH_MAP_GET(int, int, map, key);
        t_ASSERT_NOT_NULL(got);
        t_ASSERT_EQ(*got, value);
    }

    // Check all values again due to possible growth
    for (int i = 0; i < num_iter; i++) {
        int key = i;
        int value = i * 99;

        int *got = KLIB_HASH_MAP_GET(int, int, map, key);
        t_ASSERT_NOT_NULL(got);
        t_ASSERT_EQ(*got, value);
    }

    // Try key that are not in the map
    for (int i = num_iter; i < num_iter + 100; i++) {
        int *got = KLIB_HASH_MAP_GET(int, int, map, i);
        t_ASSERT_NULL(got);
    }

    return true;
}

void testsuite_hash_map() {
    t_REGISTER_TEST(test_hash_map);
    t_REGISTER_TEST(test_hash_map_bucket);
}
