// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch05/LinkedStack.c


//-------------------------------------------------------------
// �ڵ� 5.4 ����� ������ Ȱ��


#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#include "LinkedStack.h"

//-------------------------------------------------------------
// �ڵ� 5.7 ���� ��Ҹ� �Է¼����� ���
void print_stack()
{
    for (Node* p = top; p != NULL; p = p->link) {
        printf("%3d", p->data);
    }
}

void print_recur(Node* p)
{
    if (p != NULL) {
        print_recur(p->link);
        printf("%3d", p->data);
    }
}


void main()
{
    int A[7] = { 0, 1, 1, 2, 3, 5, 8 };

    init_stack();
    printf("���� �׽�Ʈ\n �Է� ������: ");
    for (int i = 0; i < 7; i++) {
        printf("%3d", A[i]);
        push(A[i]);
    }

    /*
    printf("\n�Էµ� ����");
    print_recur(top);
    printf("\n�Է��� ����");
    print_stack();
    printf("\n");
    */

    printf("\n ��� ������: ");
    while (!is_empty())
        printf("%3d", pop());
    printf("\n");

    destroy_stack();
}
