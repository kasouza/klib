# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    main.c
)

set(TESTS_EXECUTABLE test_${PROJECT_NAME})

add_executable(${TESTS_EXECUTABLE} ${SOURCES})
target_link_libraries(${TESTS_EXECUTABLE} klib)
target_include_directories(${TESTS_EXECUTABLE} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(${TESTS_EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(${TESTS_EXECUTABLE} PRIVATE c_std_17)

