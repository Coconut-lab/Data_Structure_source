// ���� 2: ���� ��� ���� ���� (������� ���)
// StackStruct.h�� ����Ͽ� ���� ǥ��� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "StackStruct.h"

// ���ڿ� ���� ����ü (���������� ��ȯ��)
typedef struct CharStack {
    char data[MAX_STACK_SIZE];
    int top;
} CharStack;

// ���� ���� �ʱ�ȭ
void init_char_stack(CharStack* s) {
    s->top = -1;
}

// ���� ������ ����ִ��� Ȯ��
int is_char_empty(CharStack* s) {
    return s->top == -1;
}

// ���� ���ÿ� �� �߰�
void push_char(CharStack* s, char c) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = c;
    }
}

// ���� ���ÿ��� �� ����
char pop_char(CharStack* s) {
    if (is_char_empty(s)) return '\0';
    return s->data[(s->top)--];
}

// ���� ������ �� �� �� Ȯ��
char peek_char(CharStack* s) {
    if (is_char_empty(s)) return '\0';
    return s->data[s->top];
}

// ���������� Ȯ��
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// ������ �켱���� ��ȯ
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

// ���� ǥ��� ��� �Լ�
int evaluate_postfix(char* expression) {
    Stack stack;  // StackStruct.h�� Stack ���
    init_stack(&stack);
    
    char* token = strtok(expression, " ");
    
    while (token != NULL) {
        // ������ ���
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            int num = atoi(token);
            push(&stack, num);  // StackStruct.h�� push ���
        }
        // �������� ���
        else if (is_operator(token[0])) {
            if (stack_size(&stack) < 2) {
                printf("�߸��� ���� ǥ����Դϴ�.\n");
                return -1;
            }
            
            // �� ���� �ǿ����ڸ� pop (���� ����!)
            int operand2 = pop(&stack);  // StackStruct.h�� pop ���
            int operand1 = pop(&stack);
            int result;
            
            // ���� ����
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
                        printf("0���� ���� �� �����ϴ�.\n");
                        return -1;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("�������� �ʴ� �������Դϴ�.\n");
                    return -1;
            }
            
            push(&stack, result);
        }
        
        token = strtok(NULL, " ");
    }
    
    // ���� ����� ���ÿ� �ϳ��� ���ƾ� ��
    if (stack_size(&stack) == 1) {
        return pop(&stack);
    } else {
        printf("�߸��� ���� ǥ����Դϴ�.\n");
        return -1;
    }
}

// ���� ǥ����� ���� ǥ������� ��ȯ
void infix_to_postfix(char* infix, char* postfix) {
    CharStack stack;
    init_char_stack(&stack);
    
    int postfix_index = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        
        // ���� ����
        if (c == ' ') continue;
        
        // �ǿ�����(����)�� ���
        if (isdigit(c)) {
            postfix[postfix_index++] = c;
            postfix[postfix_index++] = ' ';
        }
        // ���� ��ȣ�� ���
        else if (c == '(') {
            push_char(&stack, c);
        }
        // �ݴ� ��ȣ�� ���
        else if (c == ')') {
            while (!is_char_empty(&stack) && peek_char(&stack) != '(') {
                postfix[postfix_index++] = pop_char(&stack);
                postfix[postfix_index++] = ' ';
            }
            pop_char(&stack);  // '(' ����
        }
        // �������� ���
        else if (is_operator(c)) {
            while (!is_char_empty(&stack) && 
                   precedence(peek_char(&stack)) >= precedence(c)) {
                postfix[postfix_index++] = pop_char(&stack);
                postfix[postfix_index++] = ' ';
            }
            push_char(&stack, c);
        }
    }
    
    // ���ÿ� ���� �����ڵ��� ��� ���
    while (!is_char_empty(&stack)) {
        postfix[postfix_index++] = pop_char(&stack);
        postfix[postfix_index++] = ' ';
    }
    
    if (postfix_index > 0) postfix_index--;
    postfix[postfix_index] = '\0';
}

// �׽�Ʈ �Լ�
void test_calculator() {
    // �׽�Ʈ ���̽� 1
    char expr1[] = "5 1 2 + 4 * + 3 -";
    printf("������: %s\n", expr1);
    int result1 = evaluate_postfix(expr1);
    printf("���: %d\n\n", result1);
    
    // �׽�Ʈ ���̽� 2
    char expr2[] = "3 4 + 2 * 7 /";
    printf("������: %s\n", expr2);
    int result2 = evaluate_postfix(expr2);
    printf("���: %d\n\n", result2);
    
    // ���������� ��ȯ
    char infix[] = "3 + 4 * 2";
    char postfix[100];
    infix_to_postfix(infix, postfix);
    printf("����: %s �� ����: %s\n", infix, postfix);
    
    char postfix_copy[100];
    strcpy(postfix_copy, postfix);
    int result3 = evaluate_postfix(postfix_copy);
    printf("���: %d\n", result3);
}

int main() {
    test_calculator();
    return 0;
}
