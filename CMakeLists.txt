cmake_minimum_required(VERSION 3.20.0)

project(klib)

# Needed to make the language server work correctly (clangd)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DEPS_PATH ${PROJECT_SOURCE_DIR}/libs)

# Dependencies

# Library
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# Tests
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
