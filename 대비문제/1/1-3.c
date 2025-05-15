// ���� ���ϸ��� ����ϴ� ��ȣ �˻� ���α׷�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_BUFFER 100000
typedef char Element; // ���� ����� �ڷ���

// ���� ����
Element data[MAX_BUFFER]; // ���� ����� �迭
int top; // ���� ��� �ε���

// ���� �ʱ�ȭ
void init_stack() {
    top = -1;
}

// ������ ����ִ��� Ȯ��
int is_empty() {
    return (top == -1);
}

// ������ ���� á���� Ȯ��
int is_full() {
    return (top == (MAX_BUFFER - 1));
}

// ���ÿ� ��� �߰�
void push(Element e) {
    if (is_full()) {
        printf("���� �����÷ο�!\n");
        exit(1);
    }
    data[++top] = e;
}

// ���ÿ��� ��� ���� �� ��ȯ
Element pop() {
    if (is_empty()) {
        printf("���� ����÷ο�!\n");
        exit(1);
    }
    return data[top--];
}

// ��ȣ �˻� �Լ�
int check_matching(char* expr) {
    int i = 0, prev;

    init_stack();
    while (expr[i] != '\0') {
        char ch = expr[i++];
        if (ch == '[' || ch == '(' || ch == '{')
            push(ch);
        else if (ch == ']' || ch == ')' || ch == '}') {
            if (is_empty())
                return 2;       // ���� 2 ���� : ��ȣ�� ������ ���� ���

            prev = pop();
            if ((ch == ']' && prev != '[')
                || (ch == ')' && prev != '(')
                || (ch == '}' && prev != '{'))
                return 3;       // ���� 3 ���� : ��ȣ�� ������ �ٸ����
        }
    }
    if (!is_empty()) return 1;  // ���� 1 ���� : ��ȣ�� ������ ���� ���
    else return 0;              // ��ȣ ����
}

// fgets()�� ����Ͽ� �� �پ� ���� �б�
char* read_code_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("���� '%s'��(��) �� �� �����ϴ�.\n", filename);
        return NULL;
    }

    // ���� �޸� �Ҵ�
    char* code = (char*)malloc(MAX_BUFFER);
    if (code == NULL) {
        printf("�޸� �Ҵ� ����!\n");
        fclose(file);
        return NULL;
    }

    // �� ���ڿ��� �ʱ�ȭ
    code[0] = '\0';

    char line[MAX_SIZE];
    int total_length = 0;

    // �� �پ� �б�
    while (fgets(line, MAX_SIZE, file) != NULL) {
        int line_length = strlen(line);

        // ���� �����÷ο� ����
        if (total_length + line_length >= MAX_BUFFER - 1) {
            printf("������ �ʹ� Ů�ϴ�!\n");
            break;
        }

        // ���� ���� code ���� �߰�
        strcat(code, line);
        total_length += line_length;
    }

    fclose(file);
    return code;
}


int main() {
    // ������ ���� �̸� �迭
    const char* filenames[] = {
        "test01.c",
        "test02.c"
    };
    int file_count = sizeof(filenames) / sizeof(filenames[0]);

    printf("===== ��ȣ �˻� ���α׷� =====\n");

    for (int i = 0; i < file_count; i++) {
        printf("\n[���� %d] %s �˻� ��...\n", i+1, filenames[i]);

        // ���� �б� �õ�
        char* code = read_code_from_file(filenames[i]);

        if (code != NULL) {
            // ��ȣ �˻�
            int error_code = check_matching(code);

            // ��� ���
            printf("\n�˻� ���: ");
            if (error_code == 0)
                printf("����\n");
            else
                printf("����(����%d ����)\n", error_code);

            free(code);
        }
    }

    return 0;
}