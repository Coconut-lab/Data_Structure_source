#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_LINE_LENGTH 1024
#define FILE_PATH "test02.c"  // 고정 파일 경로

// 괄호 정보를 담을 구조체 정의
typedef struct {
    char bracket;
    int line;
} BracketInfo;

typedef BracketInfo Element;  // 스택 요소 타입을 BracketInfo로 설정

#include "ArrayStack.h"

// 괄호 검사 함수
void check_brackets(FILE *file) {
    char buffer[MAX_LINE_LENGTH];
    int line_number = 1;
    int total_errors = 0;

    init_stack();  // 스택 초기화

    // 파일 전체를 읽으며 괄호 처리
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        // 줄 끝의 개행 문자 제거
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
            len--;
        }

        int line_has_error = 0;  // 해당 줄에 오류가 있는지 체크

        // 현재 줄 처리
        for (int i = 0; i < len; i++) {
            char ch = buffer[i];

            // 여는 괄호 처리
            if (ch == '(' || ch == '{' || ch == '[') {
                BracketInfo info = {ch, line_number};
                push(info);  // 여는 괄호 정보를 스택에 저장
            }
            // 닫는 괄호 처리
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (is_empty()) {
                    // 닫는 괄호가 너무 많음
                    printf("오류 (라인 %d): 매칭되지 않은 닫는 괄호 '%c'\n", line_number, ch);
                    total_errors++;
                    line_has_error = 1;
                    continue;
                }

                // 괄호 짝 확인
                BracketInfo top = pop();
                if ((ch == ')' && top.bracket != '(') ||
                    (ch == '}' && top.bracket != '{') ||
                    (ch == ']' && top.bracket != '[')) {
                    // 괄호 짝 불일치
                    printf("오류 (라인 %d): 잘못된 괄호 짝 '%c'\n",
                           line_number, ch);
                    total_errors++;
                    line_has_error = 1;
                    // 잘못된 닫는 괄호가 있는 경우 해당 여는 괄호를 다시 스택에 넣어 나중에 체크
                    push(top);
                }
            }
        }

        // 해당 줄에 오류가 없으면 정상 출력
        if (!line_has_error) {
            printf("라인 %d: 정상\n", line_number);
        }

        line_number++;
    }

    // 파일을 모두 읽은 후 스택에 남아있는 여는 괄호 처리
    while (!is_empty()) {
        BracketInfo unclosed = pop();
        printf("오류 (라인 %d): 매칭되지 않은 여는 괄호 '%c'\n", unclosed.line, unclosed.bracket);
        total_errors++;
    }
}

int main() {
    FILE *file;

    // 파일 열기
    file = fopen(FILE_PATH, "r");

    // 파일 열기 실패 체크
    if (file == NULL) {
        printf("오류: '%s' 파일을 열 수 없습니다\n", FILE_PATH);
        return 1;
    }

    // 괄호 검사 실행
    check_brackets(file);

    // 파일 닫기
    fclose(file);

    return 0;
}