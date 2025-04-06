#include "klib/dynarr.test.h"
#define MAX_TESTS 32
#define KASOUZA_TEST_IMPL

#include "test.h"

int main() {
    t_REGISTER_TEST(test_dynarr);
    t_run_tests();

    return 0;
}
