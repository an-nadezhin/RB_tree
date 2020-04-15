cmake_minimum_required(VERSION 3.1)
project(RB_TREE)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        "rb_tree/rb_tree.cpp"
        "main.cpp"
)

set(HEADER_FILES
        "rb_tree/rb_tree.h"  
)
add_library(RB_TREE_LIB ${SOURCE_FILES} ${HEADER_FILES})
add_executable(RB_TREE ${SOURCE_FILES})

add_subdirectory(tests)


