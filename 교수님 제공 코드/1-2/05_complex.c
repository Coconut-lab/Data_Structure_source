// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch02/05_complex.c

//-------------------------------------------------------------
// �ڵ� 2.5 ����ü�� �Ű������� ����

#include <stdio.h>
typedef struct {
    double real;	// ���Ҽ��� �Ǽ���
    double imag;	// ���Ҽ��� �����
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

    printf("�ʱ�ȭ ����: ");
    print_complex(&a);       // call by address�� �����ϸ� �ʱ�ȭ ���Ŀ��� ���� ����
    reset_complex(&a);		// ���Ҽ� �ʱ�ȭ --> ����
    printf("�ʱ�ȭ ����: ");
    print_complex(&a);
}