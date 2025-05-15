#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 16
typedef double Element;

Element data[MAX_SIZE];
int front = 0;
int rear = 0;

void error(char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void init_queue() {
    front = rear = 0;
}

int is_empty() {
    return front == rear;
}

int is_full() {
    return (rear + 1) % MAX_SIZE == front;
}

void enqueue(Element val) {
    if (is_full()) error("ť�� ���� á���ϴ�.");
    rear = (rear + 1) % MAX_SIZE;
    data[rear] = val;
}

Element dequeue() {
    if (is_empty()) error("ť�� ��� �ֽ��ϴ�.");
    front = (front + 1) % MAX_SIZE;
    return data[front];
}

void print_queue(char msg[]) {
    printf("%s front=%d, rear=%d --> ", msg, front, rear);
    int size = (rear - front + MAX_SIZE) % MAX_SIZE;
    for (int i = front + 1; i <= front + size; i++)
        printf("%.2f ", data[i % MAX_SIZE]);
    printf("\n");
}

int main() {
    double N0, k;
    int total_time;

    printf("�ʱ� ���� �� N(0)�� �Է��ϼ���: ");
    scanf("%lf", &N0);

    printf("���� ��� k�� �Է��ϼ���: ");
    scanf("%lf", &k);

    printf("�ùķ��̼��� �� �ð� ����(����)�� �Է��ϼ���: ");
    scanf("%d", &total_time);

    init_queue();

    // ���� �ر� ��� �� ť�� ����
    for (int t = 0; t <= total_time; t++) {
        double Nt = N0 * exp(-k * t);
        enqueue(Nt);
    }

    // ť ���
    print_queue("�ð��� ���� ���� ��:");

    // ť���� �� �ϳ��� ������ ���
    printf("\n�ð��� ���� ��:\n");
    for (int t = 0; !is_empty(); t++) {
        double val = dequeue();
        printf("t = %2d, N(t) = %.4f\n", t, val);
    }

    return 0;
}
