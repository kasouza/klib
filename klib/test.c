#include "klib/dynarr.test.h"
#include "klib/hash_map.test.h"
#define MAX_TESTS 32
#define KASOUZA_TEST_IMPL

#include "test.h"

int main() {
    t_REGISTER_TEST(test_dynarr);
    testsuite_hash_map();
    t_run_tests();

    return 0;
}
