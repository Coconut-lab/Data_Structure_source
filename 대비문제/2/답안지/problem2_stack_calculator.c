// 문제 2: 스택 기반 계산기 구현 (헤더파일 사용)
// StackStruct.h를 사용하여 후위 표기법 계산기 구현

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "StackStruct.h"

// 문자용 스택 구조체 (중위→후위 변환용)
typedef struct CharStack {
    char data[MAX_STACK_SIZE];
    int top;
} CharStack;

// 문자 스택 초기화
void init_char_stack(CharStack* s) {
    s->top = -1;
}

// 문자 스택이 비어있는지 확인
int is_char_empty(CharStack* s) {
    return s->top == -1;
}

// 문자 스택에 값 추가
void push_char(CharStack* s, char c) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = c;
    }
}

// 문자 스택에서 값 제거
char pop_char(CharStack* s) {
    if (is_char_empty(s)) return '\0';
    return s->data[(s->top)--];
}

// 문자 스택의 맨 위 값 확인
char peek_char(CharStack* s) {
    if (is_char_empty(s)) return '\0';
    return s->data[s->top];
}

// 연산자인지 확인
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 연산자 우선순위 반환
int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 후위 표기법 계산 함수
int evaluate_postfix(char* expression) {
    Stack stack;  // StackStruct.h의 Stack 사용
    init_stack(&stack);
    
    char* token = strtok(expression, " ");
    
    while (token != NULL) {
        // 숫자인 경우
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            int num = atoi(token);
            push(&stack, num);  // StackStruct.h의 push 사용
        }
        // 연산자인 경우
        else if (is_operator(token[0])) {
            if (stack_size(&stack) < 2) {
                printf("잘못된 후위 표기식입니다.\n");
                return -1;
            }
            
            // 두 개의 피연산자를 pop (순서 주의!)
            int operand2 = pop(&stack);  // StackStruct.h의 pop 사용
            int operand1 = pop(&stack);
            int result;
            
            // 연산 수행
            switch(token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("0으로 나눌 수 없습니다.\n");
                        return -1;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("지원하지 않는 연산자입니다.\n");
                    return -1;
            }
            
            push(&stack, result);
        }
        
        token = strtok(NULL, " ");
    }
    
    // 최종 결과는 스택에 하나만 남아야 함
    if (stack_size(&stack) == 1) {
        return pop(&stack);
    } else {
        printf("잘못된 후위 표기식입니다.\n");
        return -1;
    }
}

// 중위 표기법을 후위 표기법으로 변환
void infix_to_postfix(char* infix, char* postfix) {
    CharStack stack;
    init_char_stack(&stack);
    
    int postfix_index = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        
        // 공백 무시
        if (c == ' ') continue;
        
        // 피연산자(숫자)인 경우
        if (isdigit(c)) {
            postfix[postfix_index++] = c;
            postfix[postfix_index++] = ' ';
        }
        // 여는 괄호인 경우
        else if (c == '(') {
            push_char(&stack, c);
        }
        // 닫는 괄호인 경우
        else if (c == ')') {
            while (!is_char_empty(&stack) && peek_char(&stack) != '(') {
                postfix[postfix_index++] = pop_char(&stack);
                postfix[postfix_index++] = ' ';
            }
            pop_char(&stack);  // '(' 제거
        }
        // 연산자인 경우
        else if (is_operator(c)) {
            while (!is_char_empty(&stack) && 
                   precedence(peek_char(&stack)) >= precedence(c)) {
                postfix[postfix_index++] = pop_char(&stack);
                postfix[postfix_index++] = ' ';
            }
            push_char(&stack, c);
        }
    }
    
    // 스택에 남은 연산자들을 모두 출력
    while (!is_char_empty(&stack)) {
        postfix[postfix_index++] = pop_char(&stack);
        postfix[postfix_index++] = ' ';
    }
    
    if (postfix_index > 0) postfix_index--;
    postfix[postfix_index] = '\0';
}

// 테스트 함수
void test_calculator() {
    // 테스트 케이스 1
    char expr1[] = "5 1 2 + 4 * + 3 -";
    printf("후위식: %s\n", expr1);
    int result1 = evaluate_postfix(expr1);
    printf("결과: %d\n\n", result1);
    
    // 테스트 케이스 2
    char expr2[] = "3 4 + 2 * 7 /";
    printf("후위식: %s\n", expr2);
    int result2 = evaluate_postfix(expr2);
    printf("결과: %d\n\n", result2);
    
    // 중위→후위 변환
    char infix[] = "3 + 4 * 2";
    char postfix[100];
    infix_to_postfix(infix, postfix);
    printf("중위: %s → 후위: %s\n", infix, postfix);
    
    char postfix_copy[100];
    strcpy(postfix_copy, postfix);
    int result3 = evaluate_postfix(postfix_copy);
    printf("결과: %d\n", result3);
}

int main() {
    test_calculator();
    return 0;
}
