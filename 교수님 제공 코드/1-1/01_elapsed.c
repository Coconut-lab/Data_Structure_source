#define _CRT_SECURE_NO_WARNINGS
// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch01/01_elapsed.c

//-------------------------------------------------------------
// �ڵ� 1.2 1���� 1������� ���� ���ϴ� �� �ɸ��� �ð� ����

int calc_sum(int n);    // �Լ��� ����Ʈ

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    clock_t start, finish;
    double  duration;

    printf("1���� 10������ ���� %d�Դϴ�.\n", calc_sum(10));

    start = clock();			// ���� �ð�
    // calc_sum(100000000);		// ����ð��� �����ϰ��� �ϴ� �ڵ带 �ִ� �κ�
    printf("1���� 1������� ���� %d�Դϴ�.\n", calc_sum(100000000));
    finish = clock();			// ���� �ð�

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("1���� 1������� ���� ���ϴµ� �ɸ� �ð�: %f ��\n", duration);
    return 0;
}

int calc_sum(int n)
{
    int i, sum = 0;
    for (i = 1; i <= n; i++)
        sum = sum + i;
    return sum;
}