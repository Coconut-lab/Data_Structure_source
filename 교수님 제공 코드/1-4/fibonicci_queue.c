// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch04/fibonacci_queue.c


// 코드 4.4 큐를 이용한 피보나치 수 구하기

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5      // 배열의 크기
typedef int Element;    // Element의 자료형 정의
#include "CircularQueue.h"

int fibonacci(int n)
{
    if (n <= 1) return n;

    init_queue();
    enqueue(0);
    enqueue(1);
    for (int i = 2; i <= n; i++) {
        int n1 = dequeue();
        int n2 = peek();
        enqueue(n1 + n2); // F(n) = F(n-2) + F(n-1)
    }
    dequeue(); // 큐에는 F(n-1), F(n)이 남아 있음
    return dequeue(); // F(n)를 반환
}

int main(void)
{
    printf("피보나치 수열: ");
    for (int i = 0; i < 16; i++)
        printf("%d,", fibonacci(i));
    printf("\n\n");

    return 0;
}
