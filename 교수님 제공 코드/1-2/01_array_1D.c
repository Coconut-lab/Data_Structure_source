// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch02/array_1D.c

//-------------------------------------------------------------
// 코드 2.1 변수와 배열의 크기 확인

#include <stdio.h>
void main()
{
    char c, cA[10];
    int i, iA[10];
    float f, fA[10];
    double d, dA[10];

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
}