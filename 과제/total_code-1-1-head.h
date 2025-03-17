#ifndef TOTAL_CODE_1_1_HEAD_H
#define TOTAL_CODE_1_1_HEAD_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_line(void) {
    printf("--------------------------------------------\n");
}

void main_screen(void) {
    print_line();
    printf("1. n개 합 구하기\n");
    printf("2. 최댓값 찾기\n");
    printf("3. 중복 요소 찾기\n");
    printf("4. 순차 탐색\n");
    printf("5. 종료\n");
    print_line();
}

int calc_sum(int n)
{
    int i, sum = 0;
    for (i = 1; i <= n; i++)
        sum = sum + i;
    return sum;
}

int find_max(int a, int b, int c) {
    int max = a;
    if (b > max ) {
        max = b;
    }
    if (c > max ) {
        max = c;
    }
    return max;
}

int has_duplicate_elem(int* A, int n)
{
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (A[i] == A[j] )   // 중복 요소 있음
                return 1;       // TRUE 반환
        }
    }
    return 0;                   // 중복 요소가 없음. FALSE 반환
}

int sequential_search(int* A, int n, int key)
{
    for (int i = 0; i<n; i++)
        if (A[i] == key)
            return i;		// 탐색이 성공하면 인덱스 반환
    return -1;			// 탐색이 실패하면 -1 반환
}

#endif //TOTAL_CODE_1_1_HEAD_H
