// 중위 표기식을 후위 표기식으로 변환하고 후위 표기식을 변환하는 프로그램

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// 스택 자료구조 정의
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// 스택 초기화 함수
void initStack(Stack *s) {
    s->top = -1;
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 스택이 가득 차 있는지 확인하는 함수
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// 스택에 요소를 추가하는 함수
void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다.\n");
        return;
    }
    s->data[++(s->top)] = item;
}

// 스택에서 요소를 제거하고 반환하는 함수
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("스택이 비었습니다.\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

// 스택의 최상위 요소를 확인하는 함수 (제거하지 않음)
char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

// 문자가 피연산자인지 확인하는 함수 (ctype.h 없이 직접 구현)
int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9');
}

// 문자가 숫자인지 확인하는 함수 (ctype.h 없이 직접 구현)
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// 연산자의 우선순위를 반환하는 함수
int getPrecedence(char operator) {
    switch (operator) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return -1;
    }
}

// 중위 표기식을 후위 표기식으로 변환하는 함수
void infixToPostfix(char infix[], char postfix[]) {
    Stack stack;
    initStack(&stack);

    int i, j = 0;
    char ch, popped;

    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        // 공백 문자는 무시
        if (ch == ' ' || ch == '\t') {
            continue;
        }

        // 피연산자(숫자나 알파벳)인 경우 바로 후위 표기식에 추가
        if (isOperand(ch)) {
            postfix[j++] = ch;
        }
        // 여는 괄호인 경우 스택에 추가
        else if (ch == '(') {
            push(&stack, ch);
        }
        // 닫는 괄호인 경우 여는 괄호를 만날 때까지 스택에서 꺼내어 후위 표기식에 추가
        else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            // 여는 괄호 제거 (출력하지 않음)
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack);
            }
        }
        // 연산자인 경우
        else {
            // 현재 연산자보다 우선순위가 높거나 같은 연산자를 스택에서 꺼내어 후위 표기식에 추가
            while (!isEmpty(&stack) && peek(&stack) != '(' &&
                   getPrecedence(ch) <= getPrecedence(peek(&stack))) {
                postfix[j++] = pop(&stack);
            }
            // 현재 연산자를 스택에 추가
            push(&stack, ch);
        }
    }

    // 스택에 남아있는 모든 연산자를 후위 표기식에 추가
    while (!isEmpty(&stack)) {
        popped = pop(&stack);
        if (popped != '(') {  // 여는 괄호는 출력하지 않음
            postfix[j++] = popped;
        }
    }

    // 문자열 종료 표시 추가
    postfix[j] = '\0';
}

// 후위 표기식을 계산하는 함수 (간단한 숫자 계산용)
double evaluatePostfix(char postfix[]) {
    Stack stack;
    initStack(&stack);

    int i;
    char ch;
    double num1, num2;

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        // 숫자인 경우 스택에 추가
        if (isDigit(ch)) {
            // 문자를 숫자로 변환하여 스택에 저장
            push(&stack, ch - '0');
        }
        // 연산자인 경우
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            // 필요한 피연산자 두 개를 스택에서 꺼냄
            num2 = pop(&stack) - '0';  // 두 번째 피연산자
            num1 = pop(&stack) - '0';  // 첫 번째 피연산자

            // 연산 수행 후 결과를 스택에 저장
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

    // 스택에 남아있는 값이 최종 결과
    return pop(&stack) - '0';
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("중위 표기식을 입력하세요: ");
    fgets(infix, MAX_SIZE, stdin);

    // 개행 문자 제거
    infix[strcspn(infix, "\n")] = '\0';

    // 중위 표기식을 후위 표기식으로 변환
    infixToPostfix(infix, postfix);

    printf("후위 표기식: %s\n", postfix);

    // 참고: 이 프로그램의 evaluatePostfix 함수는 단일 자리 숫자만 처리할 수 있습니다.
    // 또한 문자(변수) 연산은 평가하지 않습니다. 실제 계산을 위해서는 추가 개선이 필요합니다.

    return 0;
}