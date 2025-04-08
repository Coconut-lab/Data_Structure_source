// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch04/CircularDeque.c

//-------------------------------------------------------------
// 코드 4.8 원형 덱의 활용


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define Element int
#include "CircularDeque.h"

// 덱 요소의 출력 함수. front+1부터 size개의 요소를 순서대로 출력
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
        if (i % 2) add_front(i);    // i가 홀수이면 전단으로 삽입
        else add_rear(i);           // 짝수이면 후단으로 삽입
    }
    print_deque("원형 덱 홀수-짝수 ");
    printf("\tdelete_front() --> %d\n", delete_front());
    printf("\tdelete_rear () --> %d\n", delete_rear());
    printf("\tdelete_front() --> %d\n", delete_front());
    print_deque("원형 덱 삭제-홀짝홀");
}
