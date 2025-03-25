// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch03/ArrayStack.c

//-------------------------------------------------------------
// 코드 3.2 스택의 활용

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef int Element;
#include "ArrayStack.h"

void main()
{
    int A[7] = { 0, 1, 1, 2, 3, 5, 8 };
    init_stack();
    printf("스택 테스트\n 입력 데이터: ");
    for (int i = 0; i < 7; i++) {
        printf(" %d", A[i]);
        push(A[i]);
    }
    printf("\n 출력 데이터: ");
    while (!is_empty())
        printf(" %d", pop());
    printf("\n");
}
