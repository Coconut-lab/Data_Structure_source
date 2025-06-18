// 스택 구조체 헤더 파일
// StackStruct.h (큐 구조를 참고하여 제작)

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef int StackElement;  // 스택 원소의 자료형 정의

// 스택의 데이터를 구조체로 정의
typedef struct Stack {
    StackElement data[MAX_STACK_SIZE]; // 요소의 배열
    int top;                           // 스택 포인터
} Stack;

void stack_error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

void init_stack(Stack* s)
{
    s->top = -1;
}

int is_stack_empty(Stack* s)
{
    return s->top == -1;
}

int is_stack_full(Stack* s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack* s, StackElement val)
{
    if (is_stack_full(s))
        stack_error("Stack Overflow Error!");
    s->data[++(s->top)] = val;
}

StackElement pop(Stack* s)
{
    if (is_stack_empty(s))
        stack_error("Stack Underflow Error!");
    return s->data[(s->top)--];
}

StackElement stack_peek(Stack* s)
{
    if (is_stack_empty(s))
        stack_error("Stack Underflow Error!");
    return s->data[s->top];
}

// 스택의 현재 크기
int stack_size(Stack* s)
{
    return s->top + 1;
}
