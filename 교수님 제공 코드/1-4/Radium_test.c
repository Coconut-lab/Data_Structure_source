// ��缱 ���� �ùķ��̼� ���α׷�
// N(t) = N0 * e^(-kt)�� �̿��Ͽ� t�� ���� ���� ��缱 ���� ���

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// CircularQueue.h���� �ʿ��� ��ũ�ο� Ÿ�� ����
#define MAX_SIZE 100
typedef double Element;

// CircularQueue.h ����
#include "CircularQueue.h"

// ��缱 ���� �Լ�: N(t) = N0 * e^(-kt)
double calculate_radiation(double N0, double k, double t) {
    return N0 * pow(M_E, -k * t);
}

int main() {
    // 3���� ť �ʱ�ȭ (N0, k, t�� �����ϱ� ���� ť)
    Element N0_queue[MAX_SIZE];
    Element k_queue[MAX_SIZE];
    Element t_queue[MAX_SIZE];

    // ť �ʱ�ȭ (���� ������ ����ϹǷ� ť���� ������ �迭�� ���� ����)
    Element* data_backup = data;

    // N0 ť �ʱ�ȭ
    data = N0_queue;
    init_queue();

    // k ť �ʱ�ȭ
    data = k_queue;
    init_queue();

    // t ť �ʱ�ȭ
    data = t_queue;
    init_queue();

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
        // N0 ť�� �ʱ� ��缱 �� �Է�
        data = N0_queue;
        enqueue(n0);

        // k ť�� ���� ��� �Է�
        data = k_queue;
        enqueue(k);

        // t ť�� �ð� �Է�
        data = t_queue;
        enqueue(t);
    }

    // ���Ͽ��� ���� �����ͷ� ��缱 ���� ���
    fprintf(output_file, "�ʱ��缱��(N0)\t������(k)\t�ð�(t)\t\t���� ��缱��(N(t))\n");
    fprintf(output_file, "--------------------------------------------------------------------\n");

    while (1) {
        // ��� ť�� ��������� ����
        data = N0_queue;
        if (is_empty()) break;

        // ť���� �� ����
        data = N0_queue;
        double current_n0 = dequeue();

        data = k_queue;
        double current_k = dequeue();

        data = t_queue;
        double current_t = dequeue();

        // ��缱 ���� ���
        double result = calculate_radiation(current_n0, current_k, current_t);

        // ����� ���Ͽ� ���
        fprintf(output_file, "%.4lf\t\t%.4lf\t\t%.4lf\t\t%.4lf\n",
                current_n0, current_k, current_t, result);
    }

    // ���� ������ �迭 ����
    data = data_backup;

    // ���� �ݱ�
    fclose(input_file);
    fclose(output_file);

    printf("��缱 ���� �ùķ��̼��� �Ϸ�Ǿ����ϴ�.\n");
    printf("����� 'radiation_output.txt' ���Ͽ� ����Ǿ����ϴ�.\n");

    return 0;
}