cmake_minimum_required(VERSION 3.6)
project(HW_3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c )
add_library(bt binaryTree.c)
add_library(btso SHARED binaryTree.c)
include_directories('.')

add_executable(HW_3 ${SOURCE_FILES})
target_link_libraries(HW_3 bt)