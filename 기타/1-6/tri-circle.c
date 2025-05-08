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

// 리스트에 있는 값을 출력하는 함수 - 디버깅 (GPT 코드)
void print() {
    if (is_empty()) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }

    int i = 0;
    printf("=== 리스트에 저장된 좌표 ===\n");
    for (DNode* p = org.next; p != NULL; p = p->next, i++) {
        printf("좌표 #%d: (%d, %d)\n", i+1, p->data.x, p->data.y);
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
    insert(0, point); // 원점 입력

    for (int i = 0; i < 2; i++) {
        printf("좌표를 입력하세요: ");
        scanf("%d%c%d", &x, &comma, &y);

        point.x = x;
        point.y = y;

        insert(i + 1, point);
    }

    print(); // 리스트에 저장된 좌표 출력 - 디버깅 목적

    // 공식으로 삼각형의 넓이 계산
    double s; // s는 반둘레

    double area = calculator(get_entry(0), get_entry(1), get_entry(2));
    printf("삼각형의 넓이: %.2lf\n", area);

    s = calculator(get_entry(0), get_entry(1), get_entry(2));
    printf("삼각형의 반둘레: %.2lf\n", s);

    printf("내접원의 반지름: %.2lf\n", area / s);
    printf("내접원의 넓이: %.2lf\n", (area / s) * s);


    return 0;
}