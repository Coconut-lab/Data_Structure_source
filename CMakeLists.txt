cmake_minimum_required(VERSION 3.30)
project(Data_Structure_source C)

set(CMAKE_C_STANDARD 99)

add_library(Data_Structure_source STATIC test.c
        기타/1-2/first.c
        "교수님 제공 코드/1-1/01-1_elapsed.c"
        과제/total_code-1-1.c
        과제/total_code-1-1-head.h
        "교수님 제공 코드/1-2/01-1_array_1D.c"
        "교수님 제공 코드/1-2/02-1_string_test.c"
        "교수님 제공 코드/1-2/04-1_matrix.c"
        과제/1-2/total_code-1-2.c
        과제/1-2/total_code-1-2.h
        대비문제/1/1-2.c
        대비문제/1/1-3.c
        대비문제/1/calculator.c
        "교수님 제공 코드/1-3/guiHanoiTower.c"
        대비문제/1/1-4.c
        대비문제/1/1-4-solution.c
        "교수님 제공 코드/1-4/Radium.c"
        "교수님 제공 코드/1-4/Radium_ex.c"
        "교수님 제공 코드/1-4/Radium_test.c"
        "교수님 제공 코드/1-4/Upgrade_waiting_queue.c"
        "교수님 제공 코드/1-6/1-6 문제/tri-circle.c"
        대비문제/1/SelectionSort.c
        "교수님 제공 코드/1-6/1-6 문제/tri-circle2.c"
        "교수님 제공 코드/1-4/Radium_minjae.c"
        "교수님 제공 코드/1-4/Radium_minjae2.c"
        시험/01.c
        시험/02.c
        시험/03.c
        시험/04.c
        시험/05.c
        시험/06.c
        iofun.c
        대비문제/2/clean-room.c
        대비문제/2/simple-clean-room.c
        기타/reverse1.c
        기타/reverse2.c
        기타/reverse3.c
        대비문제/2/tree-clean-room.c
)

add_executable(elapsed "교수님 제공 코드/1-1/01_elapsed.c")
add_executable(01-1_elapsed "교수님 제공 코드/1-1/01-1_elapsed.c")
add_executable(01_elapsed "교수님 제공 코드/1-1/01_elapsed.c")
add_executable(02_find_max "교수님 제공 코드/1-1/02_find_max.c")
add_executable(04_sequential_search "교수님 제공 코드/1-1/04_sequential_search.c")
add_executable(total_code-1-1 과제/total_code-1-1.c)
add_executable(array_1D "교수님 제공 코드/1-2/01_array_1D.c")
add_executable(01-1_array_1D "교수님 제공 코드/1-2/01-1_array_1D.c"
        대비문제/1/1-1.c
)
add_executable(02-1_string_test "교수님 제공 코드/1-2/02-1_string_test.c")
add_executable(04-1_matrix "교수님 제공 코드/1-2/04-1_matrix.c")
add_executable(05_complex "교수님 제공 코드/1-2/05_complex.c")

add_executable(ArrayStack "교수님 제공 코드/1-3/ArrayStack.c")
add_executable(FnCallStack "교수님 제공 코드/1-3/FnCallStack.c")
add_executable(1-1 대비문제/1/1-1.c)
add_executable(1-2 대비문제/1/1-2.c)
add_executable(1-3 대비문제/1/1-3.c)
add_executable(test01 대비문제/1/test01.c)
add_executable(test02 대비문제/1/test02.c)
add_executable(eval_postfix "교수님 제공 코드/1-3/eval_postfix.c")
add_executable(calculator 대비문제/1/calculator.c)
add_executable(infix2postfix "교수님 제공 코드/1-3/infix2postfix.c")
add_executable(HanoiTower "교수님 제공 코드/1-3/HanoiTower.c")
add_executable(guiHanoiTower "교수님 제공 코드/1-3/guiHanoiTower.c")
add_executable(03_has_duplicate_elem "교수님 제공 코드/1-1/03_has_duplicate_elem.c")
add_executable(1-4 대비문제/1/1-4.c)
add_executable(1-4-solution 대비문제/1/1-4-solution.c)
add_executable(CircularQueue "교수님 제공 코드/1-4/CircularQueue.c")
add_executable(CircularDeque "교수님 제공 코드/1-4/CircularDeque.c")
add_executable(Radium "교수님 제공 코드/1-4/Radium.c")
add_executable(Radium_test "교수님 제공 코드/1-4/Radium_test.c")
add_executable(fibonicci_queue "교수님 제공 코드/1-4/fibonicci_queue.c")
add_executable(Radium_ex "교수님 제공 코드/1-4/Radium_ex.c")
add_executable(Upgrade_waiting_queue "교수님 제공 코드/1-4/Upgrade_waiting_queue.c")
add_executable(MazeDFSDeque "교수님 제공 코드/1-4/MazeDFSDeque.c")
add_executable(DynStack "교수님 제공 코드/1-5/DynStack.c")
add_executable(tri-circle "교수님 제공 코드/1-6/1-6 문제/tri-circle.c")
add_executable(test test.c)
add_executable(sort_all "교수님 제공 코드/1-9/sort_all.c")
add_executable(sort_qsort "교수님 제공 코드/1-9/sort_qsort.c")
add_executable(tri-circle2 "교수님 제공 코드/1-6/1-6 문제/tri-circle2.c")
add_executable(01 시험/01.c)
add_executable(02 시험/02.c)
add_executable(03 시험/03.c 시험/LinkedList.h)
add_executable(LinkedList "교수님 제공 코드/1-6/1-6설명/LinkedList.c")
add_executable(04 시험/04.c)
add_executable(05 시험/05.c)
add_executable(clean-room 대비문제/2/clean-room.c)
add_executable(simple-clean-room 대비문제/2/simple-clean-room.c)
add_executable(problem5_string_dictionary 대비문제/2/답안지/problem5_string_dictionary.c)
add_executable(problem6_radix_sort 대비문제/2/답안지/problem6_radix_sort.c)
add_executable(problem1_min_heap 대비문제/2/답안지/problem1_min_heap.c)
add_executable(problem2_stack_calculator 대비문제/2/답안지/problem2_stack_calculator.c)
add_executable(problem3_circular_queue 대비문제/2/답안지/problem3_circular_queue.c)
add_executable(problem4_priority_queue 대비문제/2/답안지/problem4_priority_queue.c)
add_executable(problem7_btree_node 대비문제/2/답안지/problem7_btree_node.c)
add_executable(problem8_robot_sorting 대비문제/2/답안지/problem8_robot_sorting.c)
add_executable(reverse1 기타/reverse1.c)
add_executable(reverse2 기타/reverse2.c)
add_executable(reverse3 기타/reverse3.c)
add_executable(tree-clean-room 대비문제/2/tree-clean-room.c)