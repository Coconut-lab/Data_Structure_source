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
    if (is_full()) error("큐가 가득 찼습니다.");
    rear = (rear + 1) % MAX_SIZE;
    data[rear] = val;
}

Element dequeue() {
    if (is_empty()) error("큐가 비어 있습니다.");
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

    printf("초기 방사능 양 N(0)을 입력하세요: ");
    scanf("%lf", &N0);

    printf("감쇠 상수 k를 입력하세요: ");
    scanf("%lf", &k);

    printf("시뮬레이션할 총 시간 단위(정수)를 입력하세요: ");
    scanf("%d", &total_time);

    init_queue();

    // 방사능 붕괴 계산 및 큐에 저장
    for (int t = 0; t <= total_time; t++) {
        double Nt = N0 * exp(-k * t);
        enqueue(Nt);
    }

    // 큐 출력
    print_queue("시간에 따른 방사능 양:");

    // 큐에서 값 하나씩 꺼내서 출력
    printf("\n시간별 방사능 양:\n");
    for (int t = 0; !is_empty(); t++) {
        double val = dequeue();
        printf("t = %2d, N(t) = %.4f\n", t, val);
    }

    return 0;
}
