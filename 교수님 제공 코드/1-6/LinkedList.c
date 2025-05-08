// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch06/LinkedList.c


//--------------------------------------------------------------------
// �ڵ� 6.5 ����� ������ ����Ʈ �׽�Ʈ ���α׷�


#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#include "LinkedList.h" // ����Ʈ �����Ϳ� ����

void print_list(char* msg)
{
    printf("�ܼ����Ḯ��Ʈ %s[%2d]: ", msg, size());
    for (Node* p = head; p != NULL; p = p->link)
        printf("%2d ", p->data);
    printf("\n");
}
void main()
{
    init_list(); // [ ]
    insert(0, 10); // [10]
    insert(0, 20); // [20, 10]
    insert(1, 30); // [20, 30, 10]
    insert(size(), 40); // [20, 30, 10, 40]
    insert(2, 50); // [20, 30, 50, 10, 40]
    print_list("(����x5)");

    delete(2); // [20, 30, 10, 40]
    delete(size() - 1); // [20, 30, 10]
    delete(0); // [30, 10]
    print_list("(����x3)");
    destroy_list();
}
