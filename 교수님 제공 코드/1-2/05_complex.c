// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch02/05_complex.c

//-------------------------------------------------------------
// 코드 2.5 구조체를 매개변수로 전달

#include <stdio.h>
typedef struct {
    double real;	// 복소수의 실수부
    double imag;	// 복소수의 허수부
} Complex;

void reset_complex(Complex* c) {
    c -> real = c -> imag = 0.0;
}
void print_complex(Complex* c) {
    printf("%4.1f + %4.1fi\n", c -> real, c -> imag);
}

void main()
{
    // Complex a = { 1.0, 2.0 };
    Complex a;
    a.real = 1.0;
    a.imag = 2.0;

    printf("초기화 이전: ");
    print_complex(&a);       // call by address로 구현하면 초기화 이후에도 값이 변함
    reset_complex(&a);		// 복소수 초기화 --> 실패
    printf("초기화 이후: ");
    print_complex(&a);
}