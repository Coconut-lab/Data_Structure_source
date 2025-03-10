// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch01/find_max.c

#include <stdio.h>

//-------------------------------------------------------------
// 코드 1.1 세 개의 숫자에서 최댓값을 찾는 알고리즘(C언어 표현)

int find_max(int a, int b, int c) {
    int max = a;
    if (b > max ) {
        max = b;
    }
    if (c > max ) {
        max = c;
    }
    return max;
}

//-------------------------------------------------------------
// 테스트 프로그램
void main()
{
    int max;
    max = find_max(32, 14, 5);
    printf("최댓값 = %d\n", max);
    max = find_max(5, 17, 23);
    printf("최댓값 = %d\n", max);
}