cmake_minimum_required(VERSION 3.30)
project(Data_Structure_source C)

set(CMAKE_C_STANDARD 99)

add_library(Data_Structure_source STATIC library.c
        중간/1-2/first.c
        "교수님 제공 코드/1-1/01-1_elapsed.c"
        과제/total_code-1-1.c
        과제/total_code-1-1-head.h
        "교수님 제공 코드/1-2/01-1_array_1D.c"
        "교수님 제공 코드/1-2/02-1_string_test.c"
)

add_executable(elapsed "교수님 제공 코드/1-1/01_elapsed.c")
add_executable(test 중간/1-2/first.c)
add_executable(01-1_elapsed "교수님 제공 코드/1-1/01-1_elapsed.c")
add_executable(01_elapsed "교수님 제공 코드/1-1/01_elapsed.c")
add_executable(02_find_max "교수님 제공 코드/1-1/02_find_max.c")
add_executable(04_sequential_search "교수님 제공 코드/1-1/04_sequential_search.c")
add_executable(total_code-1-1 과제/total_code-1-1.c)
add_executable(array_1D "교수님 제공 코드/1-2/01_array_1D.c")
add_executable(01-1_array_1D "교수님 제공 코드/1-2/01-1_array_1D.c")
add_executable(02-1_string_test "교수님 제공 코드/1-2/02-1_string_test.c")