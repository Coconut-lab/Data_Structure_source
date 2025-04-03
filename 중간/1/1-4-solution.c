#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ���α׷����� ����ϴ� ��� ����
 * MAX_SIZE: ������ �ִ� ũ��
 * MAX_LINE_LENGTH: �� �ٿ��� ���� �� �ִ� �ִ� ���� ��
 * FILE_PATH: �˻��� �ҽ� �ڵ� ���� ��� (������)
 */
#define MAX_SIZE 100
#define MAX_LINE_LENGTH 1024
#define FILE_PATH "test02.c"  // ���� ���� ���

/*
 * ��ȣ ������ ��� ����ü ����
 * bracket: ��ȣ ���� ('(', '{', '[', ')', '}', ']' �� �ϳ�)
 * line: �ش� ��ȣ�� �ִ� �ҽ� �ڵ��� �� ��ȣ
 */
typedef struct {
    char bracket;
    int line;
} BracketInfo;

// ���� ����� Ÿ���� BracketInfo ����ü�� ����
// ArrayStack.h ��� ������ Element Ÿ���� �����
typedef BracketInfo Element;

// ArrayStack.h ��� ���� ����
// �� ��� ���Ͽ��� ���� ���� �⺻ ������� ���ǵǾ� ����
#include "ArrayStack.h"

/**
 * �ҽ� �ڵ� ���Ͽ��� ��ȣ ¦�� �˻��ϴ� �Լ�
 *
 * �˰���:
 * 1. ������ �ʱ�ȭ�Ѵ�.
 * 2. ���Ͽ��� �� �پ� �о�´�.
 * 3. �� ���� ��� ���ڸ� ��ȸ�ϸ�:
 *    a. ���� ��ȣ('(', '{', '[')�� ������ �ش� ��ȣ�� �� ��ȣ�� ���ÿ� Ǫ���Ѵ�.
 *    b. �ݴ� ��ȣ(')', '}', ']')�� ������:
 *       i. ������ ������� ��Ī���� ���� �ݴ� ��ȣ ���� ���
 *       ii. ���ÿ��� ���� ��ȣ�� ���� ��ȣ�� ¦�� ���� ������ ���� ���
 * 4. ������ ��� �о��� �� ���ÿ� ��ȣ�� ���������� ��Ī���� ���� ���� ��ȣ ���� ���
 */
void check_brackets(FILE *file) {
    char buffer[MAX_LINE_LENGTH];  // ���Ͽ��� �� ���� �о�� ����
    int line_number = 1;           // ���� ó�� ���� �� ��ȣ
    int total_errors = 0;          // �߰ߵ� �� ���� ��

    // ���� �ʱ�ȭ (ArrayStack.h�� �Լ� ���)
    init_stack();

    // ���Ͽ��� �� �پ� �о����
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        // �� ���� ���� ���� ���� (���ڿ� ó���� ����)
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';  // ���� ���ڸ� �� ���ڷ� ��ü
            len--;                 // ���ڿ� ���� ����
        }

        // ���� ���� ���� �߻� ���θ� �����ϴ� �÷���
        int line_has_error = 0;

        // ���� ���� ��� ���� �˻�
        for (int i = 0; i < len; i++) {
            char ch = buffer[i];

            // ���� ��ȣ ó��
            if (ch == '(' || ch == '{' || ch == '[') {
                // ��ȣ ���� ����ü ���� (��ȣ ���ڿ� �� ��ȣ)
                BracketInfo info = {ch, line_number};
                // ���ÿ� ���� ����
                push(info);
            }
            // �ݴ� ��ȣ ó��
            else if (ch == ')' || ch == '}' || ch == ']') {
                // ������ ����ִ� ��� (��Ī�� ���� ��ȣ�� ����)
                if (is_empty()) {
                    printf("���� (���� %d): ��Ī���� ���� �ݴ� ��ȣ '%c'\n", line_number, ch);
                    total_errors++;
                    line_has_error = 1;
                    continue;  // ���� ���ڷ� �Ѿ
                }

                // ���ÿ��� ���� �ֱ��� ���� ��ȣ ���� ��������
                BracketInfo top = pop();

                // ���� ��ȣ�� �ݴ� ��ȣ�� ¦�� �´��� Ȯ��
                if ((ch == ')' && top.bracket != '(') ||
                    (ch == '}' && top.bracket != '{') ||
                    (ch == ']' && top.bracket != '[')) {
                    // ��ȣ ¦�� ���� �ʴ� ��� ���� ���
                    printf("���� (���� %d): �߸��� ��ȣ ¦ '%c'\n", line_number, ch);
                    total_errors++;
                    line_has_error = 1;

                    // ���� ��ȣ�� �ٽ� ���ÿ� �־ ���߿� üũ�ϵ��� ��
                    // �̷��� �ϸ� �ϳ��� �ݴ� ��ȣ ������ ��� ��ȣ ¦�� ���߸��� ���� ������ �� ����
                    push(top);
                }
            }
        }

        // ���� �ٿ� ������ ������ ���� �޽��� ���
        if (!line_has_error) {
            printf("���� %d: ����\n", line_number);
        }

        // ���� �ٷ� �̵�
        line_number++;
    }

    // ������ ��� ���� �Ŀ��� ���ÿ� ���� ��ȣ�� �����ִ��� Ȯ��
    while (!is_empty()) {
        // ���ÿ��� ���� ���� ��ȣ ���� ��������
        BracketInfo unclosed = pop();
        // ��Ī���� ���� ���� ��ȣ ���� ���
        printf("���� (���� %d): ��Ī���� ���� ���� ��ȣ '%c'\n", unclosed.line, unclosed.bracket);
        total_errors++;
    }
}

/**
 * ���� �Լ�
 * ������ ����, ��ȣ �˻� �Լ��� ȣ���� ��, ������ �ݴ� ������ ����
 */
int main() {
    FILE *file;  // ���� ������

    // ������ ����� ���� ���� (�б� ���)
    file = fopen(FILE_PATH, "r");

    // ���� ���� ���� �� ���� �޽��� ��� �� ���α׷� ����
    if (file == NULL) {
        printf("����: '%s' ������ �� �� �����ϴ�\n", FILE_PATH);
        return 1;  // ������ ���� �ڵ�
    }

    // ��ȣ �˻� �Լ� ȣ��
    check_brackets(file);

    // ����� ���� ���� �ݱ�
    fclose(file);

    return 0;  // ���� ���� �ڵ�
}