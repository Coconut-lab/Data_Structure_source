// ������ ��ȣ �˻� ���α׷� - ���� ����� ��� ��ȭ
// ���� �ڵ� ���: Check Matching R3-5.c

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100
#define MAX_FILENAME 256
#define MAX_BUFFER 100000
typedef char Element; // ���� ��� Element�� �ڷ���
#include "ArrayStack.h" // ������ ADT(�����Ϳ� ����) ����

// ��ȣ �˻� �Լ�
int check_matching(char* expr)
{
    int i = 0, prev;

    init_stack();
    while (expr[i] != '\0')
    {
        char ch = expr[i++];
        if (ch == '[' || ch == '(' || ch == '{')
            push(ch);
        else if (ch == ']' || ch == ')' || ch == '}')
        {
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

// ���� �ڵ忡 ���� ���� ��ȯ
char* get_error_message(int error_code)
{
    switch (error_code) {
        case 0: return "����: ��� ��ȣ�� ¦�� �½��ϴ�.";
        case 1: return "����(����1 ����): ��ȣ�� ������ �ʾҽ��ϴ�.";
        case 2: return "����(����2 ����): �ݴ� ��ȣ�� �����ϴ� ���� ��ȣ�� �����ϴ�.";
        case 3: return "����(����3 ����): ��ȣ�� ������ ��ġ���� �ʽ��ϴ�.";
        default: return "�� �� ���� ������ �߻��߽��ϴ�.";
    }
}

// ���Ͽ��� �ڵ� �б�
char* read_code_from_file(const char* filename)
{
    int length = 1; // ���Ṯ��
    char* code = (char*)malloc(length * sizeof(char));
    if (code == NULL) {
        printf("�޸� �Ҵ� ����!\n");
        return NULL;
    }

    code[0] = '\0'; // �ʱ�ȭ

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("���� '%s'��(��) �� �� �����ϴ�.\n", filename);
        free(code);
        return NULL;
    }

    while (!feof(file)) { // ������ ������ �о��
        char line[MAX_SIZE];
        if (fgets(line, sizeof(line), file) == NULL) {
            if (ferror(file)) {
                printf("���� '%s' �б� ���� �߻�!\n", filename);
                fclose(file);
                free(code);
                return NULL;
            }
            break; // EOF�� ����
        }

        length += strlen(line);                         // �о�� ���� ���� length�� ����
        code = realloc(code, sizeof(char) * length);    // �þ length��ŭ �ٽ� code�� �޸� ���Ҵ�
        if (code == NULL) {
            printf("�޸� ���Ҵ� ����!\n");
            fclose(file);
            return NULL;
        }
        strcat(code, line);                             // ���ڿ� ����
    }

    fclose(file);
    return code;
}

// ����� ���Ϸ� �����ϴ� �Լ�
void save_result_to_file(const char* input_filename, const char* output_filename, int error_code, char* code)
{
    FILE* outfile = fopen(output_filename, "a"); // �߰� ���� ����
    if (outfile == NULL) {
        printf("��� ���� '%s'��(��) �� �� �����ϴ�.\n", output_filename);
        return;
    }

    // �ð� ���� �߰�
    time_t current_time;
    time(&current_time);

    fprintf(outfile, "=== ��ȣ �˻� ��� ===\n");
    fprintf(outfile, "�˻� �ð�: %s", ctime(&current_time));
    fprintf(outfile, "�Է� ����: %s\n", input_filename);
    fprintf(outfile, "�˻� ���: %s\n", get_error_message(error_code));

    // �ڵ��� �Ϻ� ��� (�ʹ� ��� ����)
    fprintf(outfile, "\n�ڵ� �̸����� (ó�� 200��):\n");
    char preview[201];
    strncpy(preview, code, 200);
    preview[200] = '\0';
    fprintf(outfile, "%s\n", preview);

    if (strlen(code) > 200) {
        fprintf(outfile, "...(����)...\n");
    }

    fprintf(outfile, "\n============================\n\n");

    fclose(outfile);
    printf("����� '%s' ���Ͽ� ����Ǿ����ϴ�.\n", output_filename);
}

// ����� �������̽� ����
void interactive_mode()
{
    char input_filename[MAX_FILENAME];
    char output_filename[MAX_FILENAME];
    char choice;

    printf("=== ��ȣ �˻� ���α׷� ===\n");
    printf("����� ������ ���ϸ��� �Է��ϼ���: ");
    scanf("%255s", output_filename);
    getchar(); // ���� ����

    do {
        printf("\n�˻��� ���ϸ��� �Է��ϼ���: ");
        scanf("%255s", input_filename);
        getchar(); // ���� ����

        // �ڵ� �б�
        char* code = read_code_from_file(input_filename);
        if (code != NULL) {
            // ���� ���� �Ϻ� ���
            printf("\n���� ���� �̸�����:\n");
            int preview_len = (strlen(code) > 100) ? 100 : strlen(code);
            for (int i = 0; i < preview_len; i++) {
                putchar(code[i]);
            }
            if (strlen(code) > 100) {
                printf("\n...(����)...\n");
            } else {
                printf("\n");
            }

            // ��ȣ �˻�
            int error_code = check_matching(code);
            printf("\n�˻� ���: %s\n", get_error_message(error_code));

            // ��� ���� ����
            save_result_to_file(input_filename, output_filename, error_code, code);

            free(code);
        }

        printf("\n�ٸ� ������ �˻��Ͻðڽ��ϱ�? (y/n): ");
        scanf(" %c", &choice);
        getchar(); // ���� ����

    } while (choice == 'y' || choice == 'Y');
}

// Ŀ�ǵ� ���� ���
void command_line_mode(int argc, char* argv[])
{
    if (argc < 3) {
        printf("����: %s <�Է�����1> [�Է�����2 ...] <�������>\n", argv[0]);
        return;
    }

    char* output_filename = argv[argc - 1];

    // �Է� ���ϵ� ó��
    for (int i = 1; i < argc - 1; i++) {
        char* input_filename = argv[i];
        printf("���� '%s' ó�� ��...\n", input_filename);

        char* code = read_code_from_file(input_filename);
        if (code != NULL) {
            int error_code = check_matching(code);
            printf("�˻� ���: %s\n", get_error_message(error_code));

            save_result_to_file(input_filename, output_filename, error_code, code);

            free(code);
        }
    }
}

// ���� �ڵ��� ȣȯ ��� (���� ���� ����)
void legacy_mode()
{
    char* example[2] = {"R3-5 test01.c","R3-5 test02.c"}; // ���� �̸�
    for (int i = 0; i < 2; i++) {
        char* code = read_code_from_file(example[i]);
        if (code != NULL) {
            printf("%s\n", code);
            int errCode = check_matching(code);
            if (errCode == 0)
                printf("����\n");
            else
                printf("����(����%d ����)\n", errCode);
            free(code);
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        // Ŀ�ǵ� ���� ���ڰ� ������ Ŀ�ǵ� ���� ���� ����
        command_line_mode(argc, argv);
    }
    else {
        // ����ڿ��� ���� ��� ���� ��û
        int mode;
        printf("���� ��带 �����ϼ���:\n");
        printf("1. ��ȭ�� ��� (���ϸ� ���� �Է�)\n");
        printf("2. ���� ��� (R3-5 test01.c, R3-5 test02.c ���� �ڵ� �˻�)\n");
        printf("����: ");
        scanf("%d", &mode);
        getchar(); // ���� ����

        if (mode == 1) {
            interactive_mode();
        }
        else {
            legacy_mode();
        }
    }

    return 0;
}