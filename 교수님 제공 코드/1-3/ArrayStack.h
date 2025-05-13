// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch03/ArrayStack.h

//-------------------------------------------------------------
// 코드 3.1 배열을 이용한 스택의 구현
//-------------------------------------------------------------

#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_

#include <stdio.h>
#include <stdlib.h> // exit() 함수를 위한 헤더 추가

// 스택의 데이터(Element와 MAX_SIZE는 미리 정의되어 있어야 함)
Element data[MAX_SIZE]; // 스택 요소의 배열
int top;               // 스택 상단 인덱스

// 오류 처리 함수
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

//-------------------------------------------------------------
// 스택의 주요 연산들
//-------------------------------------------------------------

// 스택 초기화
void init_stack() {
    top = -1;
}

// 스택이 비어있는지 확인
int is_empty() {
    if (top == -1) 
        return 1;
    else 
        return 0;
}

// 스택이 가득 찼는지 확인
int is_full() {
    return (top == (MAX_SIZE - 1));
}

// 스택에 요소 추가
void push(Element e) {
    if (is_full())
        error("Overflow Error!");
    else 
        data[++top] = e;
}

// 스택에서 요소 제거 및 반환
Element pop() {
    if (is_empty())
        error("Underflow Error!");
    return data[top--];
}

// 스택의 최상위 요소 반환 (제거하지 않음)
Element peek() {
    if (is_empty())
        error("Underflow Error!");
    return data[top];
}

// 스택의 현재 크기 반환
int size() {
    return top + 1;
}

#endif