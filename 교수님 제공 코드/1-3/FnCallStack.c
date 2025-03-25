// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch03/FnCallStack.c

//-------------------------------------------------------------
// �ڵ� 3.4 ���ÿ� ����ü �����ϱ�


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
struct CallInfo { // �Լ� ȣ�� ����
    char name[32]; // �Լ��̸�
    int param; // �Ű� ����
};
typedef struct CallInfo Element;
#include "ArrayStack.h"

void main()
{
    Element calls[4] = {
        { "main()" },           // main()�Լ� ȣ��
        { "factorial()", 3 },   // factorial(3) ȣ��
        { "factorial()", 2 },   // factorial(2) ȣ��
        { "factorial()", 1 } }; // factorial(1) ȣ��

    init_stack();
    printf("�Լ� ȣ�� ����: \n");
    for (int i = 0; i < 4; i++) {
        push(calls[i]);
        printf("\t%s %d\n", calls[i].name, calls[i].param);
    }

    printf("�Լ� ��ȯ ����: \n");
    while (!is_empty()) {
        Element call = pop();
        printf("\t%s %d\n", call.name, call.param);
    }
}
