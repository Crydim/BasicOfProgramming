cmake_minimum_required(VERSION 3.27)
project(structures C)

set(CMAKE_C_STANDARD 11)

add_executable(structures main.c
        libs/data_structures/vector/vector.c
        libs/algorithm/array/array.c
        libs/data_structures/matrix/matrix.c
        libs/algorithm/function_matrix/function_matrix.c
        libs/data_structures/string/string_.c
        libs/data_structures/string/string_.h
        libs/algorithm/function__string/function__string.h
        libs/algorithm/function__string/function__string.h
        libs/algorithm/function__string/function__string.c
)

include_directories(libs/algorithm/array)
include_directories(libs/algorithm/function_matrix)
include_directories(libs/data_structures/vector)
include_directories(libs/data_structures/matrix)
include_directories(libs/data_structures/string)
include_directories(libs/algorithm/function__string)