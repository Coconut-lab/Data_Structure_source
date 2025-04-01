// 개선된 괄호 검사 프로그램 - 파일 입출력 기능 강화
// 원본 코드 기반: Check Matching R3-5.c

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100
#define MAX_FILENAME 256
#define MAX_BUFFER 100000
typedef char Element; // 스택 요소 Element의 자료형
#include "ArrayStack.h" // 스택의 ADT(데이터와 연산) 포함

// 괄호 검사 함수
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

// 오류 코드에 대한 설명 반환
char* get_error_message(int error_code)
{
    switch (error_code) {
        case 0: return "정상: 모든 괄호의 짝이 맞습니다.";
        case 1: return "오류(조건1 위반): 괄호가 닫히지 않았습니다.";
        case 2: return "오류(조건2 위반): 닫는 괄호에 대응하는 여는 괄호가 없습니다.";
        case 3: return "오류(조건3 위반): 괄호의 종류가 일치하지 않습니다.";
        default: return "알 수 없는 오류가 발생했습니다.";
    }
}

// 파일에서 코드 읽기
char* read_code_from_file(const char* filename)
{
    int length = 1; // 종료문자
    char* code = (char*)malloc(length * sizeof(char));
    if (code == NULL) {
        printf("메모리 할당 오류!\n");
        return NULL;
    }

    code[0] = '\0'; // 초기화

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일 '%s'을(를) 열 수 없습니다.\n", filename);
        free(code);
        return NULL;
    }

    while (!feof(file)) { // 파일을 끝까지 읽어옴
        char line[MAX_SIZE];
        if (fgets(line, sizeof(line), file) == NULL) {
            if (ferror(file)) {
                printf("파일 '%s' 읽기 오류 발생!\n", filename);
                fclose(file);
                free(code);
                return NULL;
            }
            break; // EOF에 도달
        }

        length += strlen(line);                         // 읽어온 글자 수를 length에 더함
        code = realloc(code, sizeof(char) * length);    // 늘어난 length만큼 다시 code에 메모리 재할당
        if (code == NULL) {
            printf("메모리 재할당 오류!\n");
            fclose(file);
            return NULL;
        }
        strcat(code, line);                             // 문자열 연결
    }

    fclose(file);
    return code;
}

// 결과를 파일로 저장하는 함수
void save_result_to_file(const char* input_filename, const char* output_filename, int error_code, char* code)
{
    FILE* outfile = fopen(output_filename, "a"); // 추가 모드로 열기
    if (outfile == NULL) {
        printf("결과 파일 '%s'을(를) 열 수 없습니다.\n", output_filename);
        return;
    }

    // 시간 정보 추가
    time_t current_time;
    time(&current_time);

    fprintf(outfile, "=== 괄호 검사 결과 ===\n");
    fprintf(outfile, "검사 시간: %s", ctime(&current_time));
    fprintf(outfile, "입력 파일: %s\n", input_filename);
    fprintf(outfile, "검사 결과: %s\n", get_error_message(error_code));

    // 코드의 일부 출력 (너무 길면 생략)
    fprintf(outfile, "\n코드 미리보기 (처음 200자):\n");
    char preview[201];
    strncpy(preview, code, 200);
    preview[200] = '\0';
    fprintf(outfile, "%s\n", preview);

    if (strlen(code) > 200) {
        fprintf(outfile, "...(생략)...\n");
    }

    fprintf(outfile, "\n============================\n\n");

    fclose(outfile);
    printf("결과가 '%s' 파일에 저장되었습니다.\n", output_filename);
}

// 사용자 인터페이스 개선
void interactive_mode()
{
    char input_filename[MAX_FILENAME];
    char output_filename[MAX_FILENAME];
    char choice;

    printf("=== 괄호 검사 프로그램 ===\n");
    printf("결과를 저장할 파일명을 입력하세요: ");
    scanf("%255s", output_filename);
    getchar(); // 버퍼 비우기

    do {
        printf("\n검사할 파일명을 입력하세요: ");
        scanf("%255s", input_filename);
        getchar(); // 버퍼 비우기

        // 코드 읽기
        char* code = read_code_from_file(input_filename);
        if (code != NULL) {
            // 파일 내용 일부 출력
            printf("\n파일 내용 미리보기:\n");
            int preview_len = (strlen(code) > 100) ? 100 : strlen(code);
            for (int i = 0; i < preview_len; i++) {
                putchar(code[i]);
            }
            if (strlen(code) > 100) {
                printf("\n...(생략)...\n");
            } else {
                printf("\n");
            }

            // 괄호 검사
            int error_code = check_matching(code);
            printf("\n검사 결과: %s\n", get_error_message(error_code));

            // 결과 파일 저장
            save_result_to_file(input_filename, output_filename, error_code, code);

            free(code);
        }

        printf("\n다른 파일을 검사하시겠습니까? (y/n): ");
        scanf(" %c", &choice);
        getchar(); // 버퍼 비우기

    } while (choice == 'y' || choice == 'Y');
}

// 커맨드 라인 모드
void command_line_mode(int argc, char* argv[])
{
    if (argc < 3) {
        printf("사용법: %s <입력파일1> [입력파일2 ...] <결과파일>\n", argv[0]);
        return;
    }

    char* output_filename = argv[argc - 1];

    // 입력 파일들 처리
    for (int i = 1; i < argc - 1; i++) {
        char* input_filename = argv[i];
        printf("파일 '%s' 처리 중...\n", input_filename);

        char* code = read_code_from_file(input_filename);
        if (code != NULL) {
            int error_code = check_matching(code);
            printf("검사 결과: %s\n", get_error_message(error_code));

            save_result_to_file(input_filename, output_filename, error_code, code);

            free(code);
        }
    }
}

// 원래 코드의 호환 모드 (기존 동작 유지)
void legacy_mode()
{
    char* example[2] = {"R3-5 test01.c","R3-5 test02.c"}; // 파일 이름
    for (int i = 0; i < 2; i++) {
        char* code = read_code_from_file(example[i]);
        if (code != NULL) {
            printf("%s\n", code);
            int errCode = check_matching(code);
            if (errCode == 0)
                printf("정상\n");
            else
                printf("오류(조건%d 위반)\n", errCode);
            free(code);
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        // 커맨드 라인 인자가 있으면 커맨드 라인 모드로 실행
        command_line_mode(argc, argv);
    }
    else {
        // 사용자에게 실행 모드 선택 요청
        int mode;
        printf("실행 모드를 선택하세요:\n");
        printf("1. 대화형 모드 (파일명 직접 입력)\n");
        printf("2. 기존 모드 (R3-5 test01.c, R3-5 test02.c 파일 자동 검사)\n");
        printf("선택: ");
        scanf("%d", &mode);
        getchar(); // 버퍼 비우기

        if (mode == 1) {
            interactive_mode();
        }
        else {
            legacy_mode();
        }
    }

    return 0;
}