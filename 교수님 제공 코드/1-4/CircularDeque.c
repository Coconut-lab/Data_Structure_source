// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch04/CircularDeque.c

//-------------------------------------------------------------
// �ڵ� 4.8 ���� ���� Ȱ��


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define Element int
#include "CircularDeque.h"

// �� ����� ��� �Լ�. front+1���� size���� ��Ҹ� ������� ���
void print_deque(char msg[]) {
    printf("%s front=%d, rear=%d --> ", msg, front, rear);
    int size = (rear - front + MAX_SIZE) % MAX_SIZE;

    for (int i = front + 1; i <= front + size; i++)
        printf("%2d ", data[i % MAX_SIZE]);
    printf("\n");
}

void main()
{
    init_deque();
    for (int i = 1; i < 10; i++) {
        if (i % 2) add_front(i);    // i�� Ȧ���̸� �������� ����
        else add_rear(i);           // ¦���̸� �Ĵ����� ����
    }
    print_deque("���� �� Ȧ��-¦�� ");
    printf("\tdelete_front() --> %d\n", delete_front());
    printf("\tdelete_rear () --> %d\n", delete_rear());
    printf("\tdelete_front() --> %d\n", delete_front());
    print_deque("���� �� ����-Ȧ¦Ȧ");
}
