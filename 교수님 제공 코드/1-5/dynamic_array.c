// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch05/dynamic_array.c


//-------------------------------------------------------------
// �ڵ� 5.1 �迭�� �������� �Ҵ��ϱ�

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void rand_array(int* A, int n)
{
    for (int i = 0; i < n; i++)
        A[i] = rand() % 100;
}
void print_array(int* A, int n)
{
    printf("�迭�� ���: ");
    for (int i = 0; i < n; i++)
        printf("%3d", A[i]);
    printf("\n");
}
double average_array(int* A, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i];
    return ((double)sum / n);
}

void main()
{
    int size;
    printf("�迭�� ũ��: ");
    scanf("%d", &size);

    int* data = (int*)malloc(sizeof(int) * size);
    rand_array(data, size);
    print_array(data, size);
    double avg = average_array(data, size);
    printf("�迭�� ���: %lf\n", avg);
    free(data);
}
