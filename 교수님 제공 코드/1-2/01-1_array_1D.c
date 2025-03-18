// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch02/array_1D.c

//-------------------------------------------------------------
// 코드 2.1 변수와 배열의 크기 확인

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    char c, cA[10];
    int i, iA[10];
    float f, fA[10];
    double d, dA[10];
    double* p1 = dA;    // 포인터 변수 선언
    double* p2[10];     // 포인터 배열 선언

    printf("<자료형의 크기 [bytes]>\n");
    printf("   char 형 = %zd  c의 크기 = %zd\n", sizeof(char), sizeof(c));
    printf("    int 형 = %zd  i의 크기 = %zd\n", sizeof(int), sizeof(i));
    printf("  float 형 = %zd  f의 크기 = %zd\n", sizeof(float), sizeof(f));
    printf(" double 형 = %zd  d의 크기 = %zd\n", sizeof(double), sizeof(d));

    printf("\n<배열의 크기와 요소의 크기 [bytes]>\n");
    printf("cA의 크기 = %zd  cA[0]의 크기 = %zd\n", sizeof(cA), sizeof(cA[0]));
    printf("iA의 크기 = %zd  iA[0]의 크기 = %zd\n", sizeof(iA), sizeof(iA[0]));
    printf("fA의 크기 = %zd  fA[0]의 크기 = %zd\n", sizeof(fA), sizeof(fA[0]));
    printf("dA의 크기 = %zd  dA[0]의 크기 = %zd\n", sizeof(dA), sizeof(dA[0]));

    printf("\n<배열 요소의 수 구하기>\n");
    printf("cA 요소의 수 = %zd 개\n", sizeof(cA) / sizeof(cA[0]));
    printf("iA 요소의 수 = %zd 개\n", sizeof(iA) / sizeof(iA[0]));
    printf("fA 요소의 수 = %zd 개\n", sizeof(fA) / sizeof(fA[0]));
    printf("dA 요소의 수 = %zd 개\n", sizeof(dA) / sizeof(dA[0]));

    printf("\n<포인터변수 크기>\n");
    printf("p1: %d\n", sizeof(p1));      // 8 bytes
    printf("dA: %d\n", sizeof(dA));      // 80 bytes
    printf("&p1: %d\n", sizeof(&p1));     // 8 bytes
    printf("*p1: %d\n", sizeof(*p1));     // 8 bytes

    printf("p2: %d\n", sizeof(p2));      // 80 bytes
    printf("&p2: %d\n", sizeof(&p2));     // 8 bytes
    printf("*p2: %d\n", sizeof(*p2));     // 8 bytes

    printf("p1+0: %d\n", sizeof(p1 + 0));  // 8 bytes
    printf("p1[0]: %d\n", sizeof(p1[0]));  // 8 bytes

    p2[0] = dA;
    *(p2[0] + 1) = 3.14;

    printf("\n<포인터 확인>\n");
    printf("*(p2[0] + 1): %lf", *(p2[0] + 1));

}