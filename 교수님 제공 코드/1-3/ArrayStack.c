// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch03/ArrayStack.c

//-------------------------------------------------------------
// �ڵ� 3.2 ������ Ȱ��

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef int Element;
#include "ArrayStack.h"

void main()
{
    int A[7] = { 0, 1, 1, 2, 3, 5, 8 };
    init_stack();
    printf("���� �׽�Ʈ\n �Է� ������: ");
    for (int i = 0; i < 7; i++) {
        printf(" %d", A[i]);
        push(A[i]);
    }
    printf("\n ��� ������: ");
    while (!is_empty())
        printf(" %d", pop());
    printf("\n");
}
