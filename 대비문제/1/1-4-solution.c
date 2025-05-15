#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 프로그램에서 사용하는 상수 정의
 * MAX_SIZE: 스택의 최대 크기
 * MAX_LINE_LENGTH: 한 줄에서 읽을 수 있는 최대 문자 수
 * FILE_PATH: 검사할 소스 코드 파일 경로 (고정값)
 */
#define MAX_SIZE 100
#define MAX_LINE_LENGTH 1024
#define FILE_PATH "test02.c"  // 고정 파일 경로

/*
 * 괄호 정보를 담는 구조체 정의
 * bracket: 괄호 문자 ('(', '{', '[', ')', '}', ']' 중 하나)
 * line: 해당 괄호가 있는 소스 코드의 줄 번호
 */
typedef struct {
    char bracket;
    int line;
} BracketInfo;

// 스택 요소의 타입을 BracketInfo 구조체로 설정
// ArrayStack.h 헤더 파일은 Element 타입을 사용함
typedef BracketInfo Element;

// ArrayStack.h 헤더 파일 포함
// 이 헤더 파일에는 스택 관련 기본 연산들이 정의되어 있음
#include "ArrayStack.h"

/**
 * 소스 코드 파일에서 괄호 짝을 검사하는 함수
 *
 * 알고리즘:
 * 1. 스택을 초기화한다.
 * 2. 파일에서 한 줄씩 읽어온다.
 * 3. 각 줄의 모든 문자를 순회하며:
 *    a. 여는 괄호('(', '{', '[')를 만나면 해당 괄호와 줄 번호를 스택에 푸시한다.
 *    b. 닫는 괄호(')', '}', ']')를 만나면:
 *       i. 스택이 비었으면 매칭되지 않은 닫는 괄호 오류 출력
 *       ii. 스택에서 팝한 괄호와 현재 괄호가 짝이 맞지 않으면 오류 출력
 * 4. 파일을 모두 읽었을 때 스택에 괄호가 남아있으면 매칭되지 않은 여는 괄호 오류 출력
 */
void check_brackets(FILE *file) {
    char buffer[MAX_LINE_LENGTH];  // 파일에서 한 줄을 읽어올 버퍼
    int line_number = 1;           // 현재 처리 중인 줄 번호
    int total_errors = 0;          // 발견된 총 오류 수

    // 스택 초기화 (ArrayStack.h의 함수 사용)
    init_stack();

    // 파일에서 한 줄씩 읽어오기
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        // 줄 끝의 개행 문자 제거 (문자열 처리를 위해)
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';  // 개행 문자를 널 문자로 대체
            len--;                 // 문자열 길이 조정
        }

        // 현재 줄의 오류 발생 여부를 추적하는 플래그
        int line_has_error = 0;

        // 현재 줄의 모든 문자 검사
        for (int i = 0; i < len; i++) {
            char ch = buffer[i];

            // 여는 괄호 처리
            if (ch == '(' || ch == '{' || ch == '[') {
                // 괄호 정보 구조체 생성 (괄호 문자와 줄 번호)
                BracketInfo info = {ch, line_number};
                // 스택에 정보 저장
                push(info);
            }
            // 닫는 괄호 처리
            else if (ch == ')' || ch == '}' || ch == ']') {
                // 스택이 비어있는 경우 (매칭될 여는 괄호가 없음)
                if (is_empty()) {
                    printf("오류 (라인 %d): 매칭되지 않은 닫는 괄호 '%c'\n", line_number, ch);
                    total_errors++;
                    line_has_error = 1;
                    continue;  // 다음 문자로 넘어감
                }

                // 스택에서 가장 최근의 여는 괄호 정보 가져오기
                BracketInfo top = pop();

                // 여는 괄호와 닫는 괄호의 짝이 맞는지 확인
                if ((ch == ')' && top.bracket != '(') ||
                    (ch == '}' && top.bracket != '{') ||
                    (ch == ']' && top.bracket != '[')) {
                    // 괄호 짝이 맞지 않는 경우 오류 출력
                    printf("오류 (라인 %d): 잘못된 괄호 짝 '%c'\n", line_number, ch);
                    total_errors++;
                    line_has_error = 1;

                    // 여는 괄호는 다시 스택에 넣어서 나중에 체크하도록 함
                    // 이렇게 하면 하나의 닫는 괄호 오류가 모든 괄호 짝을 깨뜨리는 것을 방지할 수 있음
                    push(top);
                }
            }
        }

        // 현재 줄에 오류가 없으면 정상 메시지 출력
        if (!line_has_error) {
            printf("라인 %d: 정상\n", line_number);
        }

        // 다음 줄로 이동
        line_number++;
    }

    // 파일을 모두 읽은 후에도 스택에 여는 괄호가 남아있는지 확인
    while (!is_empty()) {
        // 스택에서 남은 여는 괄호 정보 가져오기
        BracketInfo unclosed = pop();
        // 매칭되지 않은 여는 괄호 오류 출력
        printf("오류 (라인 %d): 매칭되지 않은 여는 괄호 '%c'\n", unclosed.line, unclosed.bracket);
        total_errors++;
    }
}

/**
 * 메인 함수
 * 파일을 열고, 괄호 검사 함수를 호출한 후, 파일을 닫는 역할을 수행
 */
int main() {
    FILE *file;  // 파일 포인터

    // 지정된 경로의 파일 열기 (읽기 모드)
    file = fopen(FILE_PATH, "r");

    // 파일 열기 실패 시 오류 메시지 출력 후 프로그램 종료
    if (file == NULL) {
        printf("오류: '%s' 파일을 열 수 없습니다\n", FILE_PATH);
        return 1;  // 비정상 종료 코드
    }

    // 괄호 검사 함수 호출
    check_brackets(file);

    // 사용이 끝난 파일 닫기
    fclose(file);

    return 0;  // 정상 종료 코드
}