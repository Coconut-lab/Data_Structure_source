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

// 파일에서 코드 읽기
char* read_code_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일 '%s'을(를) 열 수 없습니다.\n", filename);
        return NULL;
    }

    // 파일 크기 확인
    fseek(file, 0, SEEK_END);
    double file_size = ftell(file);
    rewind(file);

    // 충분한 메모리 할당 (파일 크기 + 여유 공간)
    char* code = (char*)malloc(file_size + 10);
    if (code == NULL) {
        printf("메모리 할당 오류!\n");
        fclose(file);
        return NULL;
    }

    // 한 번에 전체 파일 읽기
    size_t bytes_read = fread(code, 1, file_size, file);
    code[bytes_read] = '\0';  // 문자열 종료

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
            // 파일 내용 출력
            printf("\n파일 내용:\n%s\n", code);

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