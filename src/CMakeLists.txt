add_library(klib STATIC container/array_list.c container/map.c math/vec2.c math/vec3.c)
target_link_libraries(klib PUBLIC m)
target_include_directories(klib PUBLIC ${PROJECT_SOURCE_DIR}/include)