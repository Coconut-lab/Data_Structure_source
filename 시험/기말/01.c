#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define MAX_SIZE 100
typedef double Element;

typedef struct {
    Element data[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

typedef struct {
    double n0;  // 초기 방사선량
    double k;   // 붕괴상수
    double t;   // 시간
    double nt;  // N(t) 계산값
} RadiationData;

void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

void init_queue(CircularQueue* q) {
    q->front = q->rear = 0;
}

int is_empty(CircularQueue* q) {
    return q->front == q->rear;
}

int is_full(CircularQueue* q) {
    return q->front == (q->rear + 1) % MAX_SIZE;
}

void enqueue(CircularQueue* q, Element val) {
    if (is_full(q))
        error("Overflow Error!");
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = val;
}

Element dequeue(CircularQueue* q) {
    if (is_empty(q))
        error("Underflow Error!");
    q->front = (q->front + 1) % MAX_SIZE;
    return q->data[q->front];
}

double get_remaining(double N0, double k, double t) {
    return N0 * exp(-k * t);
}

void bubble_sort(RadiationData arr[], int n) {
    RadiationData temp;
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].nt > arr[j + 1].nt) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    CircularQueue N0_queue, k_queue, t_queue;
    init_queue(&N0_queue);
    init_queue(&k_queue);
    init_queue(&t_queue);

    FILE *output_file;

    srand(time(NULL));

    int count = 10;

    double n0, k, t;
    for (int i = 0; i < count; i++) {
        n0 = 100.0 + (rand() % 10001) / 100.0;
        k = 0.1 + (rand() % 10001) / 100000.0;
        t = 1.0 + (rand() % 10001) / 10000.0;

        enqueue(&N0_queue, n0);
        enqueue(&k_queue, k);
        enqueue(&t_queue, t);
    }

    RadiationData data_array[MAX_SIZE];
    int data_count = 0;

    while (!is_empty(&N0_queue)) {
        data_array[data_count].n0 = dequeue(&N0_queue);
        data_array[data_count].k = dequeue(&k_queue);
        data_array[data_count].t = dequeue(&t_queue);

        data_array[data_count].nt = get_remaining(
            data_array[data_count].n0,
            data_array[data_count].k,
            data_array[data_count].t
        );

        data_count++;
    }

    bubble_sort(data_array, data_count);

    output_file = fopen("01.txt", "w");

    fprintf(output_file, "초기방사선량(N0)\t붕괴상수(k)\t시간(년)(t)\t\t남은 방사선량(N(t))\n");
    fprintf(output_file, "--------------------------------------------------------------------\n");

    printf("초기방사선량(N0)\t붕괴상수(k)\t시간(년)(t)\t남은 방사선량(N(t))\n");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < data_count; i++) {
        fprintf(output_file, "%.4lf\t\t%.5lf\t\t%.4lf\t\t%.4lf\n",
                data_array[i].n0, data_array[i].k, data_array[i].t, data_array[i].nt);

        printf("%.4lf\t\t%.5lf\t\t%.4lf\t\t%.4lf\n",
                data_array[i].n0, data_array[i].k, data_array[i].t, data_array[i].nt);
    }

    fclose(output_file);
    printf("결과가 '01.txt' 파일에 저장되었습니다.\n");
    system("open 01.txt");

    return 0;
}