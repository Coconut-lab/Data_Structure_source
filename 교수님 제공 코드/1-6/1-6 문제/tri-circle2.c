#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
} Point;

typedef struct Node {
    Point p;
    struct Node* link;
} Node;

Node* head = NULL;

Node* create_node(double x, double y) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->p.x = x;
    new_node->p.y = y;
    new_node->link = NULL;
    return new_node;
}

void add_node(Node* input_node) {
    if (head == NULL) {
        head = input_node;
    } else {
        Node* current = head;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = input_node;
    }
}

void print_nodes() {
    Node* current = head;
    int count = 0;
    while (current != NULL) {
        printf("좌표 %d: (%.2f, %.2f)\n", count, current->p.x, current->p.y);
        current = current->link;
        count++;
    }
}

void free_nodes() {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->link;
        free(temp);
    }
    head = NULL;
}

double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

void calculate_incircle(int len, Point p1, Point p2, Point p3, Point* center, double* radius) {
    double a = distance(p2, p3);
    double b = distance(p1, p3);
    double c = distance(p1, p2);

    double perimeter = a + b + c;

    *radius = sqrt((perimeter/2 - a) * (perimeter/2 - b) * (perimeter/2 - c) / (perimeter/2));

    center->x = (a * p1.x + b * p2.x + c * p3.x) / perimeter;
    center->y = (a * p1.y + b * p2.y + c * p3.y) / perimeter;
}

int main(void) {
    int len, angle;
    double sin_val, cos_val, radius;
    Point center;

    printf("빗변의 길이와 각도를 입력하세요: ");
    scanf("%d %d", &len, &angle);

    sin_val = sin((double)angle * PI / 180);
    cos_val = cos((double)angle * PI / 180);

    Node* point1 = create_node(0, 0);
    add_node(point1);

    Node* point2 = create_node(len * cos_val, 0);
    add_node(point2);

    Node* point3 = create_node(len * cos_val, len * sin_val);
    add_node(point3);

    printf("계산된 직각삼각형의 좌표:\n");
    print_nodes();

    calculate_incircle(len ,point1->p, point2->p, point3->p, &center, &radius);

    printf("\n내접원 정보:\n");
    printf("중심점: (%.2f, %.2f)\n", center.x, center.y);
    printf("반지름: %.2f\n", radius);

    free_nodes();

    return 0;
}