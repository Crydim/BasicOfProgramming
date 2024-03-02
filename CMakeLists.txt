cmake_minimum_required(VERSION 3.27)
project(vectors C)

set(CMAKE_C_STANDARD 11)

add_executable(vectors main.c
        libs/data_structures/vector/vector.c
        libs/algorithm/array/array.c)

include_directories(libs/algorithm/array)
include_directories(libs/data_structures/vector)