// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch05/DynStack.c


//-------------------------------------------------------------
// 코드 5.3 동적 할당 스택의 활용


#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#include "DynArrayStack.h"

int main(void)
{
    MAX_SIZE = 8; // 최초의 스택 크기를 8로 설정
    init_stack(); // 스택 초기화. 동적 할당 포함

    printf("[입력] \n");
    for (int i = 0; i < 50; i++) {
        printf(" %d", i);
        push(i);
    }
    printf("\n[출력]\n");
    while (!is_empty())
        printf(" %d", pop());
    printf("\n");
    free(data);

    return 0;
}
