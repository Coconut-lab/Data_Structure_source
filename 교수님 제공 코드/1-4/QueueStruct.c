// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch04/QueueStruct.c


//-------------------------------------------------------------
// �ڵ� 4.6 ����ü�� �Ű����� ������ �̿��� ť�� Ȱ��


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 8
typedef int Element;
#include "QueueStruct.h"

void print_queue(Queue* q, char msg[]) {
    printf("%s front=%d, rear=%d --> ", msg, q->front, q->rear);
    int size = (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
    for (int i = q->front + 1; i <= q->front + size; i++)
        printf("%2d ", q->data[i % MAX_SIZE]);
    printf("\n");
}

void main()
{
    Queue q;
    init_queue(&q);
    for (int i = 1; i < 7; i++) enqueue(&q, i);
    print_queue(&q, "enqueue 1~6: ");

    for (int i = 0; i < 4; i++) dequeue(&q);
    print_queue(&q, "dequeue 4ȸ: ");
    
    for (int i = 7; i < 10; i++) enqueue(&q, i);
    print_queue(&q, "enqueue 7~9: ");
}
