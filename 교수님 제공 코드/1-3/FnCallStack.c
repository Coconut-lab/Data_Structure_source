// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch03/FnCallStack.c

//-------------------------------------------------------------
// 코드 3.4 스택에 구조체 저장하기


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
struct CallInfo { // 함수 호출 정보
    char name[32]; // 함수이름
    int param; // 매개 변수
};
typedef struct CallInfo Element;
#include "ArrayStack.h"

void main()
{
    Element calls[4] = {
        { "main()" },           // main()함수 호출
        { "factorial()", 3 },   // factorial(3) 호출
        { "factorial()", 2 },   // factorial(2) 호출
        { "factorial()", 1 } }; // factorial(1) 호출

    init_stack();
    printf("함수 호출 순서: \n");
    for (int i = 0; i < 4; i++) {
        push(calls[i]);
        printf("\t%s %d\n", calls[i].name, calls[i].param);
    }

    printf("함수 반환 순서: \n");
    while (!is_empty()) {
        Element call = pop();
        printf("\t%s %d\n", call.name, call.param);
    }
}
