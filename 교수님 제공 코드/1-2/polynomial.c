// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch02/polynomial.c

//-------------------------------------------------------------
// �ڵ� 2.7 ���׽� ���α׷�

#include <stdio.h>
#define MAX_DEGREE 1001
typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} Polynomial;
int degree(Polynomial p) // ���׽� p�� ������ ��ȯ
{
    return p.degree;
}
float coefficient(Polynomial p, int i) // ������ i�� ���� ����� ��ȯ
{
    return p.coef[i];
}
float evaluate(Polynomial p, float x) // ������ x�� ������ ����� ����� ��ȯ
{
    float result = p.coef[0];   // ����׺��� ����
    float mul = 1;              // x^i�� ���ϱ� ����
    for (int i = 1; i <= p.degree; i++) {
        mul *= x;
        result += p.coef[i] * mul;
    }
    return result;
}
Polynomial add(Polynomial a, Polynomial b) // ���׽� a�� b�� ���� ���� ��ȯ
{
    Polynomial p;
    p.degree = (a.degree > b.degree) ? a.degree : b.degree;
    for (int i = 0; i <= p.degree; i++)
        p.coef[i] = ((i <= a.degree) ? a.coef[i] : 0)
        + ((i <= b.degree) ? b.coef[i] : 0);
    return p;
}
void print_poly(Polynomial p, char str[]) // ���׽��� ȭ�鿡 ���� ���� ���
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
