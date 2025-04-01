cmake_minimum_required(VERSION 3.30)
project(Data_Structure_source C)

set(CMAKE_C_STANDARD 99)

add_library(Data_Structure_source STATIC library.c
        기타/1-2/first.c
        "교수님 제공 코드/1-1/01-1_elapsed.c"
        과제/total_code-1-1.c
        과제/total_code-1-1-head.h
        "교수님 제공 코드/1-2/01-1_array_1D.c"
        "교수님 제공 코드/1-2/02-1_string_test.c"
        "교수님 제공 코드/1-2/04-1_matrix.c"
        과제/1-2/total_code-1-2.c
        과제/1-2/total_code-1-2.h
        중간/1/1-2.c
        중간/1/1-3.c
        중간/1/calculator.c
        "교수님 제공 코드/1-3/guiHanoiTower.c"
)

add_executable(elapsed "교수님 제공 코드/1-1/01_elapsed.c")
add_executable(test 기타/1-2/first.c)
add_executable(01-1_elapsed "교수님 제공 코드/1-1/01-1_elapsed.c")
add_executable(01_elapsed "교수님 제공 코드/1-1/01_elapsed.c")
add_executable(02_find_max "교수님 제공 코드/1-1/02_find_max.c")
add_executable(04_sequential_search "교수님 제공 코드/1-1/04_sequential_search.c")
add_executable(total_code-1-1 과제/total_code-1-1.c)
add_executable(array_1D "교수님 제공 코드/1-2/01_array_1D.c")
add_executable(01-1_array_1D "교수님 제공 코드/1-2/01-1_array_1D.c"
        중간/1/1-1.c
)
add_executable(02-1_string_test "교수님 제공 코드/1-2/02-1_string_test.c")
add_executable(04-1_matrix "교수님 제공 코드/1-2/04-1_matrix.c")
add_executable(05_complex "교수님 제공 코드/1-2/05_complex.c")

add_executable(ArrayStack "교수님 제공 코드/1-3/ArrayStack.c")
add_executable(FnCallStack "교수님 제공 코드/1-3/FnCallStack.c")
add_executable(1-1 중간/1/1-1.c)
add_executable(1-2 중간/1/1-2.c)
add_executable(1-3 중간/1/1-3.c)
add_executable(test01 중간/1/test01.c)
add_executable(test02 중간/1/test02.c)
add_executable(eval_postfix "교수님 제공 코드/1-3/eval_postfix.c")
add_executable(calculator 중간/1/calculator.c)
add_executable(infix2postfix "교수님 제공 코드/1-3/infix2postfix.c")
add_executable(HanoiTower "교수님 제공 코드/1-3/HanoiTower.c")
add_executable(guiHanoiTower "교수님 제공 코드/1-3/guiHanoiTower.c")