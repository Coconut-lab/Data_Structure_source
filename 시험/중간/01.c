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
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ����� ��ȿ�� �˻�
    Point A, B, C;

    printf("�ﰢ���� ������ �� ���� ��ǥ�� �Է��ϼ��� (x1 y1 x2 y2 x3 y3): ");
    scanf("%d %d %d %d %d %d", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);

    fprintf(fp, "�Էµ� ����: A(%d, %d), B(%d, %d), C(%d, %d)\n", A.x, A.y, B.x, B.y, C.x, C.y);

    if (isTriangle(A, B, C)) {
        printf("�Էµ� ������ �ﰢ���� �����մϴ�.\n");
        fprintf(fp, "�Էµ� ������ �ﰢ���� �����մϴ�.\n");
    } else {
        printf("�Էµ� ������ �ﰢ���� �������� �ʽ��ϴ�.\n");
        fprintf(fp, "�Էµ� ������ �ﰢ���� �������� �ʽ��ϴ�.\n");
    }

    fclose(fp);
    system("open 01.txt");
    
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