#include "myheader.h"

double calculate(double a, double b, char op) {
    double res = 0.0;
    
    switch(op) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            if(b != 0) {
                res = a / b;
            } else {
                printf("오류: 0으로 나눌 수 없습니다.\n");
                res = 0.0;
            }
            break;
        default:
            printf("오류: 잘못된 연산자입니다.\n");
            res = 0.0;
            break;
    }
    
    return res;
}
