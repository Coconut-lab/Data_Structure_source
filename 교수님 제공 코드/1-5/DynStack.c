// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch05/DynStack.c


//-------------------------------------------------------------
// �ڵ� 5.3 ���� �Ҵ� ������ Ȱ��


#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#include "DynArrayStack.h"

int main(void)
{
    MAX_SIZE = 8; // ������ ���� ũ�⸦ 8�� ����
    init_stack(); // ���� �ʱ�ȭ. ���� �Ҵ� ����

    printf("[�Է�] \n");
    for (int i = 0; i < 50; i++) {
        printf(" %d", i);
        push(i);
    }
    printf("\n[���]\n");
    while (!is_empty())
        printf(" %d", pop());
    printf("\n");
    free(data);

    return 0;
}
