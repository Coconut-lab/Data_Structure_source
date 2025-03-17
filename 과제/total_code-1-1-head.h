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
    printf("1. n�� �� ���ϱ�\n");
    printf("2. �ִ� ã��\n");
    printf("3. �ߺ� ��� ã��\n");
    printf("4. ���� Ž��\n");
    printf("5. ����\n");
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
            if (A[i] == A[j] )   // �ߺ� ��� ����
                return 1;       // TRUE ��ȯ
        }
    }
    return 0;                   // �ߺ� ��Ұ� ����. FALSE ��ȯ
}

int sequential_search(int* A, int n, int key)
{
    for (int i = 0; i<n; i++)
        if (A[i] == key)
            return i;		// Ž���� �����ϸ� �ε��� ��ȯ
    return -1;			// Ž���� �����ϸ� -1 ��ȯ
}

#endif //TOTAL_CODE_1_1_HEAD_H
