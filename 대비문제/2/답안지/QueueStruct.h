// 구조체를 이용한 원형 큐 헤더 파일
// QueueStruct.h (교수님 제공 코드 기반)

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef int Element;  // 큐 원소의 자료형 정의

// 원형 큐의 데이터를 구조체로 정의
typedef struct Queue {
    Element data[MAX_SIZE]; // 요소의 배열
    int front;              // 전단 인덱스
    int rear;               // 후단 인덱스
} Queue;

void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

void init_queue(Queue* q)
{
    q->front = q->rear = 0;
}

int is_empty(Queue* q)
{
    return q->front == q->rear;
}

int is_full(Queue* q)
{
    return q->front == (q->rear + 1) % MAX_SIZE;
}

void enqueue(Queue* q, Element val)
{
    if (is_full(q))
        error("Overflow Error!");
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = val;
}

Element dequeue(Queue* q)
{
    if (is_empty(q))
        error("Underflow Error!");
    q->front = (q->front + 1) % MAX_SIZE;
    return q->data[q->front];
}

Element peek(Queue* q)
{
    if (is_empty(q))
        error("Underflow Error!");
    return q->data[(q->front + 1) % MAX_SIZE];
}

// 큐의 현재 크기
int size(Queue* q)
{
    return (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
}
