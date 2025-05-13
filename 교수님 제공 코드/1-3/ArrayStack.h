// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch03/ArrayStack.h

//-------------------------------------------------------------
// �ڵ� 3.1 �迭�� �̿��� ������ ����
//-------------------------------------------------------------

#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_

#include <stdio.h>
#include <stdlib.h> // exit() �Լ��� ���� ��� �߰�

// ������ ������(Element�� MAX_SIZE�� �̸� ���ǵǾ� �־�� ��)
Element data[MAX_SIZE]; // ���� ����� �迭
int top;               // ���� ��� �ε���

// ���� ó�� �Լ�
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

//-------------------------------------------------------------
// ������ �ֿ� �����
//-------------------------------------------------------------

// ���� �ʱ�ȭ
void init_stack() {
    top = -1;
}

// ������ ����ִ��� Ȯ��
int is_empty() {
    if (top == -1) 
        return 1;
    else 
        return 0;
}

// ������ ���� á���� Ȯ��
int is_full() {
    return (top == (MAX_SIZE - 1));
}

// ���ÿ� ��� �߰�
void push(Element e) {
    if (is_full())
        error("Overflow Error!");
    else 
        data[++top] = e;
}

// ���ÿ��� ��� ���� �� ��ȯ
Element pop() {
    if (is_empty())
        error("Underflow Error!");
    return data[top--];
}

// ������ �ֻ��� ��� ��ȯ (�������� ����)
Element peek() {
    if (is_empty())
        error("Underflow Error!");
    return data[top];
}

// ������ ���� ũ�� ��ȯ
int size() {
    return top + 1;
}

#endif