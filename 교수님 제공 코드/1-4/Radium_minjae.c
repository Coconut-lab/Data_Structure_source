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
        printf("ť�� ���� á���ϴ�.\n");
        return;
    }
    rear = (rear + 1) % MAX_SIZE;
    data[rear] = item;
}

RadiationData dequeue() {
    if (is_empty()) {
        printf("ť�� ����ֽ��ϴ�.\n");
        exit(1);
    }
    front = (front + 1) % MAX_SIZE;
    return data[front];
}

void print_queue(char msg[]) {
    printf("%s\n", msg);
    printf("�ð�\t��缱��\n");
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

    // �ʱ� ��缱�� ���� (100���� ����)
    double initial_radiation = 100.0;
    double half_life = 5.0; // �ݰ��� (�ð� ����)

    // 20�ð� ������ �ùķ��̼�
    for (int time = 0; time < 20; time++) {
        RadiationData rd;
        rd.time_step = time;
        // �����Լ��� �ر� ����: N = N0 * e^(-��t)
        // ���⼭ �� = ln(2)/half_life
        double decay_constant = log(2) / half_life;
        rd.radiation_level = initial_radiation * exp(-decay_constant * time);

        // �ణ�� ���� ������ �߰�
        rd.radiation_level += (rand() % 10 - 5) * 0.1;

        enqueue(rd);
    }

    print_queue("��缱 �ر� �ùķ��̼� ���:");

    return 0;
}