// ��缱 ���� �ùķ��̼� ���α׷�
// N(t) = N0 * e^(-kt)�� �̿��Ͽ� t�� ���� ���� ��缱 ���� ���

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// CircularQueue.h���� �ʿ��� ��ũ�ο� Ÿ�� ����
#define MAX_SIZE 100
typedef double Element;

// ť ����ü ����
typedef struct {
    Element data[MAX_SIZE]; // ����� �迭
    int front;              // ���� �ε���
    int rear;               // �Ĵ� �ε���
} CircularQueue;

// ť ���� �Լ� ����
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

Element peek(CircularQueue* q) {
    if (is_empty(q))
        error("Underflow Error!");
    return q->data[(q->front + 1) % MAX_SIZE];
}

// ��缱 ���� �Լ�: N(t) = N0 * e^(-kt)
double calculate_radiation(double N0, double k, double t) {
    return N0 * exp(-k * t);  // pow(M_E, -k * t) ��� exp �Լ� ���
}

int main() {
    // 3���� ť �ʱ�ȭ (N0, k, t�� �����ϱ� ���� ť)
    CircularQueue N0_queue, k_queue, t_queue;

    // ť �ʱ�ȭ
    init_queue(&N0_queue);
    init_queue(&k_queue);
    init_queue(&t_queue);

    FILE *input_file, *output_file;

    // �Է� ���� ����
    input_file = fopen("radiation_input.txt", "r");
    if (input_file == NULL) {
        printf("�Է� ������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ��� ���� ����
    output_file = fopen("radiation_output.txt", "w");
    if (output_file == NULL) {
        printf("��� ������ ������ �� �����ϴ�.\n");
        fclose(input_file);
        return 1;
    }

    // ���Ͽ��� ������ �б�
    double n0, k, t;
    while (fscanf(input_file, "%lf %lf %lf", &n0, &k, &t) == 3) {
        // �� ť�� ������ �Է�
        enqueue(&N0_queue, n0);
        enqueue(&k_queue, k);
        enqueue(&t_queue, t);
    }

    // ���Ͽ��� ���� �����ͷ� ��缱 ���� ���
    fprintf(output_file, "�ʱ��缱��(N0)\t������(k)\t�ð�(t)\t\t���� ��缱��(N(t))\n");
    fprintf(output_file, "--------------------------------------------------------------------\n");

    while (!is_empty(&N0_queue)) {
        // ť���� �� ����
        double current_n0 = dequeue(&N0_queue);
        double current_k = dequeue(&k_queue);
        double current_t = dequeue(&t_queue);

        // ��缱 ���� ���
        double result = calculate_radiation(current_n0, current_k, current_t);

        // ����� ���Ͽ� ���
        fprintf(output_file, "%.4lf\t\t%.4lf\t\t%.4lf\t\t%.4lf\n",
                current_n0, current_k, current_t, result);
    }

    // ���� �ݱ�
    fclose(input_file);
    fclose(output_file);

    printf("��缱 ���� �ùķ��̼��� �Ϸ�Ǿ����ϴ�.\n");
    printf("����� 'radiation_output.txt' ���Ͽ� ����Ǿ����ϴ�.\n");

    return 0;
}