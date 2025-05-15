#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Point {
    int x;
    int y;
};
typedef struct Point Element;

#include "DblLinkedList.h"

// ����Ʈ�� �ִ� ���� ����ϴ� �Լ� - ����� (GPT �ڵ�)
void print() {
    if (is_empty()) {
        printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
        return;
    }

    int i = 0;
    printf("=== ����Ʈ�� ����� ��ǥ ===\n");
    for (DNode* p = org.next; p != NULL; p = p->next, i++) {
        printf("��ǥ #%d: (%d, %d)\n", i+1, p->data.x, p->data.y);
    }
    printf("==========================\n");
}

double calculator(Element a, Element b, Element c) {
    double s = (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)) +
                sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2)) +
                sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2))) / 2;

    return sqrt(s * (s - sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2))) *
                (s - sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2))) *
                (s - sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2))));
}

int main(void) {
    int x, y;
    char comma;
    Element point;

    init_list();

    point.x = 0;
    point.y = 0;
    insert(0, point); // ���� �Է�

    for (int i = 0; i < 2; i++) {
        printf("��ǥ�� �Է��ϼ���: ");
        scanf("%d%c%d", &x, &comma, &y);

        point.x = x;
        point.y = y;

        insert(i + 1, point);
    }

    print(); // ����Ʈ�� ����� ��ǥ ��� - ����� ����

    // �������� �ﰢ���� ���� ���
    double s; // s�� �ݵѷ�

    double area = calculator(get_entry(0), get_entry(1), get_entry(2));
    printf("�ﰢ���� ����: %.2lf\n", area);

    s = calculator(get_entry(0), get_entry(1), get_entry(2));
    printf("�ﰢ���� �ݵѷ�: %.2lf\n", s);

    printf("�������� ������: %.2lf\n", area / s);
    printf("�������� ����: %.2lf\n", (area / s) * s);


    return 0;
}