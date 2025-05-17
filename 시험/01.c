#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { int x, y; } Point;

double distance(Point p1, Point p2);
int isTriangle(Point A, Point B, Point C);

int main(void) {
    FILE *fp = fopen("01.txt", "w");
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

    if (isTriangle(A, B, C)) {
        printf("입력된 점들은 삼각형을 형성합니다.\n");
        fprintf(fp, "입력된 점들은 삼각형을 형성합니다.\n");
    } else {
        printf("입력된 점들은 삼각형을 형성하지 않습니다.\n");
        fprintf(fp, "입력된 점들은 삼각형을 형성하지 않습니다.\n");
    }

    fclose(fp);
    system("open 01.txt");
    
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