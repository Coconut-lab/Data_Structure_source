// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch03/reverse_str.c

//-------------------------------------------------------------
// 코드 3.3 문자열 뒤집어 출력하기

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2000
typedef char Element;
#include "ArrayStack.h"

void main()
{
    char str[200];

    init_stack();
    printf("문자열 입력: ");
    gets_s(str, 200);
    for (int i = 0; str[i] != '\0'; i++)
        push(str[i]);

    printf("문자열 출력: ");
    while (!is_empty())
        putchar(pop());
    printf("\n");
}

