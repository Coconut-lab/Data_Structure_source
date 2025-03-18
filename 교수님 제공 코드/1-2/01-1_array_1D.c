// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch02/array_1D.c

//-------------------------------------------------------------
// �ڵ� 2.1 ������ �迭�� ũ�� Ȯ��

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
    double* p1 = dA;    // ������ ���� ����
    double* p2[10];     // ������ �迭 ����

    printf("<�ڷ����� ũ�� [bytes]>\n");
    printf("   char �� = %zd  c�� ũ�� = %zd\n", sizeof(char), sizeof(c));
    printf("    int �� = %zd  i�� ũ�� = %zd\n", sizeof(int), sizeof(i));
    printf("  float �� = %zd  f�� ũ�� = %zd\n", sizeof(float), sizeof(f));
    printf(" double �� = %zd  d�� ũ�� = %zd\n", sizeof(double), sizeof(d));

    printf("\n<�迭�� ũ��� ����� ũ�� [bytes]>\n");
    printf("cA�� ũ�� = %zd  cA[0]�� ũ�� = %zd\n", sizeof(cA), sizeof(cA[0]));
    printf("iA�� ũ�� = %zd  iA[0]�� ũ�� = %zd\n", sizeof(iA), sizeof(iA[0]));
    printf("fA�� ũ�� = %zd  fA[0]�� ũ�� = %zd\n", sizeof(fA), sizeof(fA[0]));
    printf("dA�� ũ�� = %zd  dA[0]�� ũ�� = %zd\n", sizeof(dA), sizeof(dA[0]));

    printf("\n<�迭 ����� �� ���ϱ�>\n");
    printf("cA ����� �� = %zd ��\n", sizeof(cA) / sizeof(cA[0]));
    printf("iA ����� �� = %zd ��\n", sizeof(iA) / sizeof(iA[0]));
    printf("fA ����� �� = %zd ��\n", sizeof(fA) / sizeof(fA[0]));
    printf("dA ����� �� = %zd ��\n", sizeof(dA) / sizeof(dA[0]));

    printf("\n<�����ͺ��� ũ��>\n");
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

    printf("\n<������ Ȯ��>\n");
    printf("*(p2[0] + 1): %lf", *(p2[0] + 1));

}