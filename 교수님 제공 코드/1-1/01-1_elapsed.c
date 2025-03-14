#define _CRT_SECURE_NO_WARNINGS
// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch01/01_elapsed.c

//-------------------------------------------------------------
// �ڵ� 1.2 1���� 1������� ���� ���ϴ� �� �ɸ��� �ð� ����
#define MAX1 10
#define MAX2 100000000

int calc_sum(int n);    // �Լ��� ����Ʈ

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE* fp1 = fopen("01_output.txt", "a+");
    clock_t start, finish;
    double  duration;

    fprintf(stdout ,"1���� 10������ ���� %d�Դϴ�.\n", calc_sum(MAX1));
    fprintf(fp1, "1���� 10������ ���� %d�Դϴ�.\n", calc_sum(MAX1));

    start = clock();			// ���� �ð�
    calc_sum(MAX2);		// ����ð��� �����ϰ��� �ϴ� �ڵ带 �ִ� �κ�
    finish = clock();			// ���� �ð�

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    fprintf(stdout, "1���� 1������� ���� ���ϴµ� �ɸ� �ð�: %lf ��\n", duration);
    fprintf(fp1, "1���� 1������� ���� ���ϴµ� �ɸ� �ð�: %lf ��\n", duration);

    fprintf(fp1, "-------------------------------------------------\n");

    fclose(fp1);
    system("open -a TextEdit 01_output.txt");

    return 0;
}

int calc_sum(int n)
{
    int i, sum = 0;
    for (i = 1; i <= n; i++)
        sum = sum + i;
    return sum;
}