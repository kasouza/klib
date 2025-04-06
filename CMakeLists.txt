cmake_minimum_required(VERSION 3.30)
project(klib)

# Set some global configs
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIB_NAME lib_${PROJECT_NAME})
set(TEST_NAME test_${PROJECT_NAME})

# Main library
add_library(
    ${LIB_NAME} STATIC

    klib/dummy.c
)

target_compile_features(${LIB_NAME} PRIVATE c_std_17)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

# Test executable
add_executable(
    ${TEST_NAME}

    klib/test.c
    klib/dynarr.test.c
    klib/hash_map.test.c
)

target_compile_features(${TEST_NAME} PRIVATE c_std_17)
target_link_libraries(${TEST_NAME} PRIVATE ${LIB_NAME})
