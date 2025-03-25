// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch03/infix2postfix.c

//-------------------------------------------------------------
// 코드 3.7 중위 식의 후위 표기식 변환 프로그램

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef char Element; // 스택에는 연산자가 저장됨
#include "ArrayStack.h"

int precedence(char op)
{
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

void infix_to_postfix(char expr[])
{
    init_stack();

    int i = 0;
    while (expr[i] != '\0') {
        char c = expr[i++];
        if ((c >= '0' && c <= '9')) {
            printf("%c ", c);
        }
        else if (c == '(')
            push(c);
        else if (c == ')') {
            while (is_empty() == 0) {
                char op = pop();
                if (op == '(') break;
                else printf("%c ", op);
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (is_empty() == 0) {
                char op = peek();
                if (precedence(c) <= precedence(op)) {
                    printf("%c ", op);
                    pop();
                }
                else break;
            }
            push(c);
        }
    }
    while (is_empty() == 0)
        printf("%c ", pop());
    printf("\n");
}

void main()
{
    char expr[2][80] = { "8 / 2 - 3 + (3 * 2)", "1 / 2 * 4 * (1 / 4)" };

    printf("중위수식: %s ==> 후위수식:", expr[0]);
    infix_to_postfix(expr[0]);
    printf("중위수식: %s ==> 후위수식:", expr[1]);
    infix_to_postfix(expr[1]);
}

