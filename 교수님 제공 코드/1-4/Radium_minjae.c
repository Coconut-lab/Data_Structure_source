#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 100

typedef struct {
    double radiation_level;
    int time_step;
} RadiationData;

RadiationData data[MAX_SIZE];
int front = 0, rear = 0;

void init_queue() {
    front = rear = 0;
}

int is_empty() {
    return front == rear;
}

int is_full() {
    return (rear + 1) % MAX_SIZE == front;
}

void enqueue(RadiationData item) {
    if (is_full()) {
        printf("큐가 가득 찼습니다.\n");
        return;
    }
    rear = (rear + 1) % MAX_SIZE;
    data[rear] = item;
}

RadiationData dequeue() {
    if (is_empty()) {
        printf("큐가 비어있습니다.\n");
        exit(1);
    }
    front = (front + 1) % MAX_SIZE;
    return data[front];
}

void print_queue(char msg[]) {
    printf("%s\n", msg);
    printf("시간\t방사선량\n");
    printf("----------------\n");

    int size = (rear - front + MAX_SIZE) % MAX_SIZE;
    for (int i = front + 1; i <= front + size; i++) {
        int idx = i % MAX_SIZE;
        printf("%d\t%.2f\n", data[idx].time_step, data[idx].radiation_level);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    init_queue();

    // 초기 방사선량 설정 (100으로 설정)
    double initial_radiation = 100.0;
    double half_life = 5.0; // 반감기 (시간 단위)

    // 20시간 동안의 시뮬레이션
    for (int time = 0; time < 20; time++) {
        RadiationData rd;
        rd.time_step = time;
        // 지수함수적 붕괴 공식: N = N0 * e^(-λt)
        // 여기서 λ = ln(2)/half_life
        double decay_constant = log(2) / half_life;
        rd.radiation_level = initial_radiation * exp(-decay_constant * time);

        // 약간의 랜덤 노이즈 추가
        rd.radiation_level += (rand() % 10 - 5) * 0.1;

        enqueue(rd);
    }

    print_queue("방사선 붕괴 시뮬레이션 결과:");

    return 0;
}