add_library(klib STATIC vector.c map.c)
target_include_directories(klib PUBLIC ${PROJECT_SOURCE_DIR}/include)