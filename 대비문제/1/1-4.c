#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_LINE_LENGTH 1024
#define FILE_PATH "test02.c"  // ���� ���� ���

// ��ȣ ������ ���� ����ü ����
typedef struct {
    char bracket;
    int line;
} BracketInfo;

typedef BracketInfo Element;  // ���� ��� Ÿ���� BracketInfo�� ����

#include "ArrayStack.h"

// ��ȣ �˻� �Լ�
void check_brackets(FILE *file) {
    char buffer[MAX_LINE_LENGTH];
    int line_number = 1;
    int total_errors = 0;

    init_stack();  // ���� �ʱ�ȭ

    // ���� ��ü�� ������ ��ȣ ó��
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        // �� ���� ���� ���� ����
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
            len--;
        }

        int line_has_error = 0;  // �ش� �ٿ� ������ �ִ��� üũ

        // ���� �� ó��
        for (int i = 0; i < len; i++) {
            char ch = buffer[i];

            // ���� ��ȣ ó��
            if (ch == '(' || ch == '{' || ch == '[') {
                BracketInfo info = {ch, line_number};
                push(info);  // ���� ��ȣ ������ ���ÿ� ����
            }
            // �ݴ� ��ȣ ó��
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (is_empty()) {
                    // �ݴ� ��ȣ�� �ʹ� ����
                    printf("���� (���� %d): ��Ī���� ���� �ݴ� ��ȣ '%c'\n", line_number, ch);
                    total_errors++;
                    line_has_error = 1;
                    continue;
                }

                // ��ȣ ¦ Ȯ��
                BracketInfo top = pop();
                if ((ch == ')' && top.bracket != '(') ||
                    (ch == '}' && top.bracket != '{') ||
                    (ch == ']' && top.bracket != '[')) {
                    // ��ȣ ¦ ����ġ
                    printf("���� (���� %d): �߸��� ��ȣ ¦ '%c'\n",
                           line_number, ch);
                    total_errors++;
                    line_has_error = 1;
                    // �߸��� �ݴ� ��ȣ�� �ִ� ��� �ش� ���� ��ȣ�� �ٽ� ���ÿ� �־� ���߿� üũ
                    push(top);
                }
            }
        }

        // �ش� �ٿ� ������ ������ ���� ���
        if (!line_has_error) {
            printf("���� %d: ����\n", line_number);
        }

        line_number++;
    }

    // ������ ��� ���� �� ���ÿ� �����ִ� ���� ��ȣ ó��
    while (!is_empty()) {
        BracketInfo unclosed = pop();
        printf("���� (���� %d): ��Ī���� ���� ���� ��ȣ '%c'\n", unclosed.line, unclosed.bracket);
        total_errors++;
    }
}

int main() {
    FILE *file;

    // ���� ����
    file = fopen(FILE_PATH, "r");

    // ���� ���� ���� üũ
    if (file == NULL) {
        printf("����: '%s' ������ �� �� �����ϴ�\n", FILE_PATH);
        return 1;
    }

    // ��ȣ �˻� ����
    check_brackets(file);

    // ���� �ݱ�
    fclose(file);

    return 0;
}