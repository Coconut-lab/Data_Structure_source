// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch06/ArrayList.c


//--------------------------------------------------------------------
// �ڵ� 6.2 �迭 ������ ����Ʈ �׽�Ʈ ���α׷�


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef int Element;
#include "ArrayList.h" // ����Ʈ �����Ϳ� ����

void print_list(char* msg)
{
    printf("�迭��������Ʈ %s[%2d]: ", msg, size);
    for (int i = 0; i < size; i++)
        printf("%2d ", data[i]);
    printf("\n");
}
void main()
{
    init_list();        // [ ]
    insert(0, 10);      // [10]
    insert(0, 20);      // [20, 10]
    insert(1, 30);      // [20, 30, 10]
    insert(size, 40);   // [20, 30, 10, 40]
    insert(2, 50);      // [20, 30, 50, 10, 40]
    print_list("(����x5)");

    delete(2);          // [20, 30, 10, 40]
    delete(size - 1);   // [20, 30, 10]
    delete(0);          // [30, 10]
    print_list("(����x3)");
}
