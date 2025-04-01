// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch03/eval_postfix.c

//-------------------------------------------------------------
// �ڵ� 3.6 ���� ǥ��� ��� ���α׷�


#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef double Element; // ���ÿ��� �ǿ�����(double)�� �����
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
            double val2 = pop(); // �� ��° �ǿ�����
            double val1 = pop(); // ù ��° �ǿ�����
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

    printf("����: %s = %lf\n", expr[0], eval_postfix(expr[0]));
    printf("����: %s = %lf\n", expr[1], eval_postfix(expr[1]));
}
