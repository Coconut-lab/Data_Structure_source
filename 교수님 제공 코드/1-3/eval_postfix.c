// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch03/eval_postfix.c

//-------------------------------------------------------------
// 코드 3.6 후위 표기식 계산 프로그램


#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef double Element; // 스택에는 피연산자(double)가 저장됨
#include "ArrayStack.h"

double eval_postfix(char* expr)
{
    int i = 0;

    init_stack();
    while (expr[i] != '\0') {
        char c = expr[i++];
        if (c >= '0' && c <= '9') {
            double num = (double)c - '0';
            push(num);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            double val2 = pop(); // 두 번째 피연산자
            double val1 = pop(); // 첫 번째 피연산자
            switch (c) {
            case '+': push(val1 + val2); break;
            case '-': push(val1 - val2); break;
            case '*': push(val1 * val2); break;
            case '/': push(val1 / val2); break;
            }
        }
    }
    return pop();
}

void main()
{
    char expr[2][80] = { "8 2 / 3- 3 2 * +", "1 2 / 4 * 1 4 / *" };

    printf("수식: %s = %lf\n", expr[0], eval_postfix(expr[0]));
    printf("수식: %s = %lf\n", expr[1], eval_postfix(expr[1]));
}
