// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch04/QueueStruct.c


//-------------------------------------------------------------
// 코드 4.6 구조체와 매개변수 전달을 이용한 큐의 활용


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
    print_queue(&q, "dequeue 4회: ");
    
    for (int i = 7; i < 10; i++) enqueue(&q, i);
    print_queue(&q, "enqueue 7~9: ");
}
