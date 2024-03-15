cmake_minimum_required(VERSION 3.27)
project(structures C)

set(CMAKE_C_STANDARD 11)

add_executable(structures main.c
        libs/data_structures/vector/vector.c
        libs/algorithm/array/array.c
        libs/data_structures/Matrix/matrix.c
)

include_directories(libs/algorithm/array)
include_directories(libs/data_structures/vector)
include_directories(libs/data_structures/Matrix)