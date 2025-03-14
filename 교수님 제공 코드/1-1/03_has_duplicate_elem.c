// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch01/03_has_duplicate_elem.c

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


//-------------------------------------------------------------
// �ڵ� 1.4 �迭�� �ߺ� ��Ұ� �ִ��� �˻�

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

//-------------------------------------------------------------
// �׽�Ʈ ���α׷�
void main()
{
    int a[8] = { 32, 14, 5, 17, 23, 9, 11, 4 };
    int b[8] = { 32, 14, 5, 17, 23, 14, 11, 4 };

    printf("A: �ߺ��� ��� %s\n", has_duplicate_elem(a,8) ? "����" : "����");
    printf("B: �ߺ��� ��� %s\n", has_duplicate_elem(b,8) ? "����" : "����");
}