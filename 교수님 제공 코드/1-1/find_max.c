// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch01/find_max.c

#include <stdio.h>

//-------------------------------------------------------------
// �ڵ� 1.1 �� ���� ���ڿ��� �ִ��� ã�� �˰���(C��� ǥ��)

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

//-------------------------------------------------------------
// �׽�Ʈ ���α׷�
void main()
{
    int max;
    max = find_max(32, 14, 5);
    printf("�ִ� = %d\n", max);
    max = find_max(5, 17, 23);
    printf("�ִ� = %d\n", max);
}