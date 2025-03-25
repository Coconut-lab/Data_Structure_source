// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch02/03_array_func.c

//-------------------------------------------------------------
// 코드 2.3 함수의 매개변수로 배열 전달

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


// 추상화
void reset_variable(int);
void reset_array(int* , int);

void main()
{
    int A[3] = { 10, 20, 30 }, x = 2024;

    reset_variable(x);		// 변수 x를 0으로 초기화 -> 실패
    reset_array(A, 3);		// 길이가 3인 배열 A를 0으로 초기화 -> 성공

    printf("변수 초기화: x=%d\n", x);        // x=2024
    printf("배열 초기화: ");                 // A[0]=0 A[1]=0 A[2]=0
    for (int i=0; i < 3 ; i++)
        printf("A[%d]=%d ", i, A[i]);
    printf("\n");
}

void reset_variable(int a) {
    a = 0;
}
void reset_array(int* a, int len) {
    for (int i = 0; i < len; i++)
      a[i] = 0;
}