// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch02/polynomial.c

//-------------------------------------------------------------
// 코드 2.7 다항식 프로그램

#include <stdio.h>
#define MAX_DEGREE 1001
typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} Polynomial;
int degree(Polynomial p) // 다항식 p의 차수를 반환
{
    return p.degree;
}
float coefficient(Polynomial p, int i) // 지수가 i인 항의 계수를 반환
{
    return p.coef[i];
}
float evaluate(Polynomial p, float x) // 미지수 x를 대입해 계산한 결과를 반환
{
    float result = p.coef[0];   // 상수항부터 시작
    float mul = 1;              // x^i를 구하기 위함
    for (int i = 1; i <= p.degree; i++) {
        mul *= x;
        result += p.coef[i] * mul;
    }
    return result;
}
Polynomial add(Polynomial a, Polynomial b) // 다항식 a와 b의 합을 구해 반환
{
    Polynomial p;
    p.degree = (a.degree > b.degree) ? a.degree : b.degree;
    for (int i = 0; i <= p.degree; i++)
        p.coef[i] = ((i <= a.degree) ? a.coef[i] : 0)
        + ((i <= b.degree) ? b.coef[i] : 0);
    return p;
}
void print_poly(Polynomial p, char str[]) // 다항식을 화면에 보기 좋게 출력
{
    printf(" %s", str);
    for (int i = p.degree; i > 0; i--)
        printf("%5.1f x^%d + ", p.coef[i], i);
    printf("%4.1f\n", p.coef[0]);
}
void main()
{
    Polynomial a = { 5, { 3, 6, 0, 0, 0, 10} };
    Polynomial b = { 4, { 7, 0, 5, 0, 1} };
    Polynomial c = add(a, b);
    print_poly(a, " A = ");
    print_poly(b, " B = ");
    print_poly(c, "A+B= ");
    printf("A(1)= %f\n", evaluate(a, 1.0f));
    printf("B(2)= %f\n", evaluate(b, 2.0f));
}
