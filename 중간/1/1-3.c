// 고정 파일명을 사용하는 괄호 검사 프로그램
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_BUFFER 100000
typedef char Element; // 스택 요소의 자료형

// 스택 구현
Element data[MAX_BUFFER]; // 스택 요소의 배열
int top; // 스택 상단 인덱스

// 스택 초기화
void init_stack() {
    top = -1;
}

// 스택이 비어있는지 확인
int is_empty() {
    return (top == -1);
}

// 스택이 가득 찼는지 확인
int is_full() {
    return (top == (MAX_BUFFER - 1));
}

// 스택에 요소 추가
void push(Element e) {
    if (is_full()) {
        printf("스택 오버플로우!\n");
        exit(1);
    }
    data[++top] = e;
}

// 스택에서 요소 제거 및 반환
Element pop() {
    if (is_empty()) {
        printf("스택 언더플로우!\n");
        exit(1);
    }
    return data[top--];
}

// 괄호 검사 함수
int check_matching(char* expr) {
    int i = 0, prev;

    init_stack();
    while (expr[i] != '\0') {
        char ch = expr[i++];
        if (ch == '[' || ch == '(' || ch == '{')
            push(ch);
        else if (ch == ']' || ch == ')' || ch == '}') {
            if (is_empty())
                return 2;       // 조건 2 위반 : 괄호가 열리지 않은 경우

            prev = pop();
            if ((ch == ']' && prev != '[')
                || (ch == ')' && prev != '(')
                || (ch == '}' && prev != '{'))
                return 3;       // 조건 3 위반 : 괄호의 종류가 다른경우
        }
    }
    if (!is_empty()) return 1;  // 조건 1 위반 : 괄호가 닫히지 않은 경우
    else return 0;              // 괄호 정상
}

// fgets()를 사용하여 한 줄씩 파일 읽기
char* read_code_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일 '%s'을(를) 열 수 없습니다.\n", filename);
        return NULL;
    }

    // 동적 메모리 할당
    char* code = (char*)malloc(MAX_BUFFER);
    if (code == NULL) {
        printf("메모리 할당 오류!\n");
        fclose(file);
        return NULL;
    }

    // 빈 문자열로 초기화
    code[0] = '\0';

    char line[MAX_SIZE];
    int total_length = 0;

    // 한 줄씩 읽기
    while (fgets(line, MAX_SIZE, file) != NULL) {
        int line_length = strlen(line);

        // 버퍼 오버플로우 방지
        if (total_length + line_length >= MAX_BUFFER - 1) {
            printf("파일이 너무 큽니다!\n");
            break;
        }

        // 현재 줄을 code 끝에 추가
        strcat(code, line);
        total_length += line_length;
    }

    fclose(file);
    return code;
}


int main() {
    // 고정된 파일 이름 배열
    const char* filenames[] = {
        "test01.c",
        "test02.c"
    };
    int file_count = sizeof(filenames) / sizeof(filenames[0]);

    printf("===== 괄호 검사 프로그램 =====\n");

    for (int i = 0; i < file_count; i++) {
        printf("\n[파일 %d] %s 검사 중...\n", i+1, filenames[i]);

        // 파일 읽기 시도
        char* code = read_code_from_file(filenames[i]);

        if (code != NULL) {
            // 괄호 검사
            int error_code = check_matching(code);

            // 결과 출력
            printf("\n검사 결과: ");
            if (error_code == 0)
                printf("정상\n");
            else
                printf("오류(조건%d 위반)\n", error_code);

            free(code);
        }
    }

    return 0;
}