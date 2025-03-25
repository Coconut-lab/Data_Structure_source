// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch02/03_array_func.c

//-------------------------------------------------------------
// �ڵ� 2.3 �Լ��� �Ű������� �迭 ����

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


// �߻�ȭ
void reset_variable(int);
void reset_array(int* , int);

void main()
{
    int A[3] = { 10, 20, 30 }, x = 2024;

    reset_variable(x);		// ���� x�� 0���� �ʱ�ȭ -> ����
    reset_array(A, 3);		// ���̰� 3�� �迭 A�� 0���� �ʱ�ȭ -> ����

    printf("���� �ʱ�ȭ: x=%d\n", x);        // x=2024
    printf("�迭 �ʱ�ȭ: ");                 // A[0]=0 A[1]=0 A[2]=0
    for (int i=0; i < 3 ; i++)
        printf("A[%d]=%d ", i, A[i]);
    printf("\n");
}

void reset_variable(int a) {
    a = 0;
}
void reset_array(int* a, int len) {
    for (int i = 0; i < len; i++)
      a[i] = 0;
}