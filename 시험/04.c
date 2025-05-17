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
    printf("단순연결리스트 %s[%2d]: ", msg, size());
    for (Node* p = head; p != NULL; p = p->link)
        printf("%.2lf ", p->data);
    printf("\n");
}

int main(void) {
    FILE *fp = fopen("04.txt", "w");
    int num = 1;

    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 삼격형 유효성 검사
    Point A, B, C;

    printf("삼각형을 구성할 세 점의 좌표를 입력하세요 (x1 y1 x2 y2 x3 y3): ");
    scanf("%d %d %d %d %d %d", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);

    fprintf(fp, "입력된 점들: A(%d, %d), B(%d, %d), C(%d, %d)\n", A.x, A.y, B.x, B.y, C.x, C.y);

    double D, E, F, G;

    if (isTriangle(A, B, C)) {
        double x, y;
        D = (distance(A, B) + distance(B, C) + distance(C, A)) / 2;
        E = calculateTriangle(distance(A, B), distance(B, C), distance(C, A));
        F = E / D;
        G = safeArea(F, F);

        printf("연결리스트 출력\n");
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

        // 내접원의 중심 좌표 계산
        x = (distance(A, B) * A.x + distance(B, C) * B.x + distance(C, A) * C.x) / (distance(A, B) + distance(B, C) + distance(C, A));
        y = (distance(A, B) * A.y + distance(B, C) * B.y + distance(C, A) * C.y) / (distance(A, B) + distance(B, C) + distance(C, A));
        printf("내접원의 중심 좌표: (%.4f, %.4f)\n", x, y);
        fprintf(fp, "내접원의 중심 좌표: (%.4f, %.4f)\n", x, y);

        printf("A(%d, %d) -> B(%d, %d) -> C(%d, %d) -> D(%.4f) -> E(%.4f) -> F(%.4f) -> H(%0.4f, %0.4f) -> G(%.4f)\n", A.x, A.y, B.x, B.y, C.x, C.y, D, E, F, x, y, G);
        fprintf(fp, "A(%d, %d) -> B(%d, %d) -> C(%d, %d) -> D(%.4f) -> E(%.4f) -> F(%.4f) -> H(%0.4f, %0.4f) -> G(%.4f)\n", A.x, A.y, B.x, B.y, C.x, C.y, D, E, F, x, y, G);

        insert(10, x);
        insert(11, y);


        destroy_list();

    } else {
        printf("입력된 점들은 삼각형을 형성하지 않습니다.\n");
        fprintf(fp, "입력된 점들은 삼각형을 형성하지 않습니다.\n");
    }

    fclose(fp);
    system("open 04.txt");

    return 0;
}

// 거리 계산 함수
double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// 삼갹형 유효성 검사 함수
int isTriangle(Point A, Point B, Point C) {
    double AB = distance(A, B);
    double BC = distance(B, C);
    double CA = distance(C, A);

    return (AB + BC > CA) && (AB + CA > BC) && (BC + CA > AB);
}

// 삼각형 넓이 계산 함수
double calculateTriangle(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
// 안전 구역 계산 함수 - 내접원 넓이
double safeArea(double a, double b) {
    return M_PI * a * b;
}