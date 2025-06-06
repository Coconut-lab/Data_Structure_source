#include "myheader.h"

double num1, num2, result;
char operator;

void myInput(void) {
    printf("숫자와 연산자를 입력하시오: ");
    scanf("%lf %lf %c", &num1, &num2, &operator);
}

void myOutput(void) {
    printf("%.2f\n", result);
}
