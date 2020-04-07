cmake_minimum_required(VERSION 3.10)
project(Glad VERSION 0.0.1)

add_library(glad
    src/glad.c
)

target_include_directories(glad 
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(glad
    PUBLIC
    GL
    GLU
)
