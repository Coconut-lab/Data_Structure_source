// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch03/reverse_str.c

//-------------------------------------------------------------
// �ڵ� 3.3 ���ڿ� ������ ����ϱ�

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2000
typedef char Element;
#include "ArrayStack.h"

void main()
{
    char str[200];

    init_stack();
    printf("���ڿ� �Է�: ");
    gets_s(str, 200);
    for (int i = 0; str[i] != '\0'; i++)
        push(str[i]);

    printf("���ڿ� ���: ");
    while (!is_empty())
        putchar(pop());
    printf("\n");
}

