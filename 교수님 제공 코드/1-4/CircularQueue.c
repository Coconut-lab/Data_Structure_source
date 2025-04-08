// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch04/CircularQueue.c


//-------------------------------------------------------------
// 코드 4.2 원형 큐의 활용

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 8

typedef int Element;
#include "CircularQueue.h"

void print_queue(char msg[]) { // 큐의 내용을 화면에 출력하는 함수
    printf("%s front=%d, rear=%d --> ", msg, front, rear);
    int size = (rear - front + MAX_SIZE) % MAX_SIZE;
    for (int i = front + 1; i <= front + size; i++)
        printf("%2d ", data[i % MAX_SIZE]);
    printf("\n");
}

void main()
{
    init_queue();
    for (int i = 1; i < 7; i++) enqueue(i);
    print_queue("enqueue 1~6: ");

    for (int i = 0; i < 4; i++) dequeue();
    print_queue("dequeue 4회: ");

    for (int i = 7; i < 10; i++) enqueue(i);
    print_queue("enqueue 7~9: ");
}
