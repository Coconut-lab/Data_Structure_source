// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch02/string_test.c

//-------------------------------------------------------------
// 코드 2.2 문자열 테스트

#include <stdio.h>
#include <string.h>             // 문자열 복사, 길이 계산 등의 함수 사용을 위해
void main()
{
    char s1[16] = "Hello World";
    char s2[] = "Hello World";
    char s3[16] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0' };
    char s4[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd' };
    char s5[20];

    //s4 = s1;                  // 오류: 문자열은 대입 연산자로 복사 불가
    strcpy_s(s5, 20, s1);       // 문자열 s1을 크기가 20인 문자배열 s5에 복사

    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);
    printf("s3: %s\n", s3);
    printf("s4: %s\n", s4);
    printf("s5: %s\n", s5);
    printf("문자열 s1의 길이: %zd\n", strlen(s1));
    printf("문자열 s2의 길이: %zd\n", strlen(s2));
}
