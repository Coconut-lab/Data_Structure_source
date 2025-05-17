#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double Element;
#include "LinkedList.h"

typedef struct { int x, y; } Point;

double distance(Point p1, Point p2);
int isTriangle(Point A, Point B, Point C);
double calculateTriangle(double, double, double);
double safeArea(double, double);

void print_list(char* msg)
{
    printf("�ܼ����Ḯ��Ʈ %s[%2d]: ", msg, size());
    for (Node* p = head; p != NULL; p = p->link)
        printf("%.2lf ", p->data);
    printf("\n");
}

int main(void) {
    FILE *fp = fopen("04.txt", "w");
    int num = 1;

    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ����� ��ȿ�� �˻�
    Point A, B, C;

    printf("�ﰢ���� ������ �� ���� ��ǥ�� �Է��ϼ��� (x1 y1 x2 y2 x3 y3): ");
    scanf("%d %d %d %d %d %d", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);

    fprintf(fp, "�Էµ� ����: A(%d, %d), B(%d, %d), C(%d, %d)\n", A.x, A.y, B.x, B.y, C.x, C.y);

    double D, E, F, G;

    if (isTriangle(A, B, C)) {
        double x, y;
        D = (distance(A, B) + distance(B, C) + distance(C, A)) / 2;
        E = calculateTriangle(distance(A, B), distance(B, C), distance(C, A));
        F = E / D;
        G = safeArea(F, F);

        printf("���Ḯ��Ʈ ���\n");
        printf("A(%d, %d) -> B(%d, %d) -> C(%d, %d) -> D(%.4f) -> E(%.4f) -> F(%.4f) -> G(%.4f)\n", A.x, A.y, B.x, B.y, C.x, C.y, D, E, F, G);
        fprintf(fp, "A(%d, %d) -> B(%d, %d) -> C(%d, %d) -> D(%.4f) -> E(%.4f) -> F(%.4f) -> G(%.4f)\n", A.x, A.y, B.x, B.y, C.x, C.y, D, E, F, G);

        init_list();
        insert(0, 0);
        insert(1, A.x);
        insert(2, A.y);
        insert(3, B.x);
        insert(4, B.y);
        insert(5, C.x);
        insert(6, C.y);
        insert(7, D);
        insert(8, E);
        insert(9, F);
        insert(10, G);

        // �������� �߽� ��ǥ ���
        x = (distance(A, B) * A.x + distance(B, C) * B.x + distance(C, A) * C.x) / (distance(A, B) + distance(B, C) + distance(C, A));
        y = (distance(A, B) * A.y + distance(B, C) * B.y + distance(C, A) * C.y) / (distance(A, B) + distance(B, C) + distance(C, A));
        printf("�������� �߽� ��ǥ: (%.4f, %.4f)\n", x, y);
        fprintf(fp, "�������� �߽� ��ǥ: (%.4f, %.4f)\n", x, y);

        printf("A(%d, %d) -> B(%d, %d) -> C(%d, %d) -> D(%.4f) -> E(%.4f) -> F(%.4f) -> H(%0.4f, %0.4f) -> G(%.4f)\n", A.x, A.y, B.x, B.y, C.x, C.y, D, E, F, x, y, G);
        fprintf(fp, "A(%d, %d) -> B(%d, %d) -> C(%d, %d) -> D(%.4f) -> E(%.4f) -> F(%.4f) -> H(%0.4f, %0.4f) -> G(%.4f)\n", A.x, A.y, B.x, B.y, C.x, C.y, D, E, F, x, y, G);

        insert(10, x);
        insert(11, y);


        destroy_list();

    } else {
        printf("�Էµ� ������ �ﰢ���� �������� �ʽ��ϴ�.\n");
        fprintf(fp, "�Էµ� ������ �ﰢ���� �������� �ʽ��ϴ�.\n");
    }

    fclose(fp);
    system("open 04.txt");

    return 0;
}

// �Ÿ� ��� �Լ�
double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// �ﰽ�� ��ȿ�� �˻� �Լ�
int isTriangle(Point A, Point B, Point C) {
    double AB = distance(A, B);
    double BC = distance(B, C);
    double CA = distance(C, A);

    return (AB + BC > CA) && (AB + CA > BC) && (BC + CA > AB);
}

// �ﰢ�� ���� ��� �Լ�
double calculateTriangle(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
// ���� ���� ��� �Լ� - ������ ����
double safeArea(double a, double b) {
    return M_PI * a * b;
}