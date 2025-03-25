// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch03/factorial.c

#include <stdio.h>

//-------------------------------------------------------------
// 코드 3.8 반복 구조의 팩토리얼 함수
int factorial_iter(int n)
{
    int i, result = 1;
    for (i = 1; i <= n; i++)
        result = result * i;
    return result;
}

//-------------------------------------------------------------
// 코드 3.9 순환 구조의 팩토리얼 함수
int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

//----------------------------------------------------------------------
// 순환 호출과 반환 과정 출력을 위한 순환 알고리즘 수정
int factorial_p(int n)
{
    printf("함수 호출: factorial(%d)\n", n);	// 순환호출 순서 확인을 위한 출력문
    int ret;
    if (n == 1) ret = 1;
    else ret = n * factorial_p(n - 1);

    // 함수의 반환 위치를 한 곳으로 모아 출력
    printf("함수 반환: factorial(%d) --> %d\n", n, ret);
    return ret;
}
//----------------------------------------------------------------------


void main()
{
    printf("반복 factorial(3) = %d\n", factorial_iter(3));
    printf("순환 factorial(3) = %d\n", factorial(3));

    factorial_p(3);
}
