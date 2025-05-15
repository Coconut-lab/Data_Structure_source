// ���� ǥ����� ���� ǥ������� ��ȯ�ϰ� ���� ǥ����� ��ȯ�ϴ� ���α׷�

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// ���� �ڷᱸ�� ����
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// ���� �ʱ�ȭ �Լ�
void initStack(Stack *s) {
    s->top = -1;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Stack *s) {
    return s->top == -1;
}

// ������ ���� �� �ִ��� Ȯ���ϴ� �Լ�
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ�
void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("������ ���� á���ϴ�.\n");
        return;
    }
    s->data[++(s->top)] = item;
}

// ���ÿ��� ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("������ ������ϴ�.\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

// ������ �ֻ��� ��Ҹ� Ȯ���ϴ� �Լ� (�������� ����)
char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

// ���ڰ� �ǿ��������� Ȯ���ϴ� �Լ� (ctype.h ���� ���� ����)
int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9');
}

// ���ڰ� �������� Ȯ���ϴ� �Լ� (ctype.h ���� ���� ����)
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// �������� �켱������ ��ȯ�ϴ� �Լ�
int getPrecedence(char operator) {
    switch (operator) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return -1;
    }
}

// ���� ǥ����� ���� ǥ������� ��ȯ�ϴ� �Լ�
void infixToPostfix(char infix[], char postfix[]) {
    Stack stack;
    initStack(&stack);

    int i, j = 0;
    char ch, popped;

    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        // ���� ���ڴ� ����
        if (ch == ' ' || ch == '\t') {
            continue;
        }

        // �ǿ�����(���ڳ� ���ĺ�)�� ��� �ٷ� ���� ǥ��Ŀ� �߰�
        if (isOperand(ch)) {
            postfix[j++] = ch;
        }
        // ���� ��ȣ�� ��� ���ÿ� �߰�
        else if (ch == '(') {
            push(&stack, ch);
        }
        // �ݴ� ��ȣ�� ��� ���� ��ȣ�� ���� ������ ���ÿ��� ������ ���� ǥ��Ŀ� �߰�
        else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            // ���� ��ȣ ���� (������� ����)
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack);
            }
        }
        // �������� ���
        else {
            // ���� �����ں��� �켱������ ���ų� ���� �����ڸ� ���ÿ��� ������ ���� ǥ��Ŀ� �߰�
            while (!isEmpty(&stack) && peek(&stack) != '(' &&
                   getPrecedence(ch) <= getPrecedence(peek(&stack))) {
                postfix[j++] = pop(&stack);
            }
            // ���� �����ڸ� ���ÿ� �߰�
            push(&stack, ch);
        }
    }

    // ���ÿ� �����ִ� ��� �����ڸ� ���� ǥ��Ŀ� �߰�
    while (!isEmpty(&stack)) {
        popped = pop(&stack);
        if (popped != '(') {  // ���� ��ȣ�� ������� ����
            postfix[j++] = popped;
        }
    }

    // ���ڿ� ���� ǥ�� �߰�
    postfix[j] = '\0';
}

// ���� ǥ����� ����ϴ� �Լ� (������ ���� ����)
double evaluatePostfix(char postfix[]) {
    Stack stack;
    initStack(&stack);

    int i;
    char ch;
    double num1, num2;

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        // ������ ��� ���ÿ� �߰�
        if (isDigit(ch)) {
            // ���ڸ� ���ڷ� ��ȯ�Ͽ� ���ÿ� ����
            push(&stack, ch - '0');
        }
        // �������� ���
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            // �ʿ��� �ǿ����� �� ���� ���ÿ��� ����
            num2 = pop(&stack) - '0';  // �� ��° �ǿ�����
            num1 = pop(&stack) - '0';  // ù ��° �ǿ�����

            // ���� ���� �� ����� ���ÿ� ����
            switch (ch) {
                case '+':
                    push(&stack, (num1 + num2) + '0');
                    break;
                case '-':
                    push(&stack, (num1 - num2) + '0');
                    break;
                case '*':
                    push(&stack, (num1 * num2) + '0');
                    break;
                case '/':
                    push(&stack, (num1 / num2) + '0');
                    break;
                case '^': {
                    double result = 1;
                    for (int j = 0; j < num2; j++) {
                        result *= num1;
                    }
                    push(&stack, result + '0');
                    break;
                }
            }
        }
    }

    // ���ÿ� �����ִ� ���� ���� ���
    return pop(&stack) - '0';
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("���� ǥ����� �Է��ϼ���: ");
    fgets(infix, MAX_SIZE, stdin);

    // ���� ���� ����
    infix[strcspn(infix, "\n")] = '\0';

    // ���� ǥ����� ���� ǥ������� ��ȯ
    infixToPostfix(infix, postfix);

    printf("���� ǥ���: %s\n", postfix);

    // ����: �� ���α׷��� evaluatePostfix �Լ��� ���� �ڸ� ���ڸ� ó���� �� �ֽ��ϴ�.
    // ���� ����(����) ������ ������ �ʽ��ϴ�. ���� ����� ���ؼ��� �߰� ������ �ʿ��մϴ�.

    return 0;
}