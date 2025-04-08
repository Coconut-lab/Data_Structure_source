#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 8

// Element Ÿ�� ���� - ��缱 �ر� �ùķ��̼��� ���� ����ü
typedef struct {
    double initialAmount;    // �ʱ� ��缺 ������ ��(g)
    double decayConstant;    // �ر� ���(lambda)
    double time;             // ��� �ð�(��)
} Element;

#include "CircularQueue.h"

// ť ������ ȭ�鿡 ����ϴ� �Լ�
void print_queue(char msg[]) {
    printf("%s front=%d, rear=%d --> \n", msg, front, rear);
    int size = (rear - front + MAX_SIZE) % MAX_SIZE;

    for (int i = front + 1; i <= front + size; i++) {
        int idx = i % MAX_SIZE;
        printf("�ùķ��̼� %d: �ʱⷮ=%.6fg, �ر����=%.8f/��, �ð�=%.2f��\n",
               i - front, data[idx].initialAmount, data[idx].decayConstant, data[idx].time);
    }
    printf("\n");
}

// ��缱 �ر� ��� �� ��� ��� �Լ�
void calculate_decay(Element elem) {
    double remainingAmount = elem.initialAmount * exp(-elem.decayConstant * elem.time);
    double activityInitial = elem.initialAmount * elem.decayConstant;
    double activityFinal = remainingAmount * elem.decayConstant;
    double halfLife = log(2) / elem.decayConstant;

    printf("\n===== ���� �ر� ��� ��� =====\n");
    printf("�ʱ� ��缺 ������ ��: %.6f g\n", elem.initialAmount);
    printf("�ݰ���: %.2f ��\n", halfLife);
    printf("�ر� ���(��): %.8f /��\n", elem.decayConstant);
    printf("��� �ð�: %.2f ��\n", elem.time);
    printf("���� ��缺 ������ ��: %.6f g\n", remainingAmount);
    printf("���� ����: %.2f%%\n", (1 - remainingAmount/elem.initialAmount) * 100);
    printf("�ʱ� ���� Ȱ����(����): %.6e Bq\n", activityInitial);
    printf("���� ���� Ȱ����(����): %.6e Bq\n", activityFinal);
    printf("==============================\n\n");
}

// �ùķ��̼� ������ �Է� �Լ�
Element input_simulation_data() {
    Element elem;

    printf("�ʱ� ��缺 ������ ��(g)�� �Է��ϼ���: ");
    scanf("%lf", &elem.initialAmount);

    printf("�ݰ���(��)�� �Է��ϼ���: ");
    double halfLife;
    scanf("%lf", &halfLife);
    elem.decayConstant = log(2) / halfLife;

    printf("��� �ð�(��)�� �Է��ϼ���: ");
    scanf("%lf", &elem.time);

    return elem;
}

int main() {
    init_queue();
    int choice;

    while (1) {
        printf("\n====== ��缱 �ر� �ùķ��̼� ======\n");
        printf("1. ���ο� �ùķ��̼� �߰�\n");
        printf("2. �ùķ��̼� ��� �� ����\n");
        printf("3. ���� �ùķ��̼� ��� ����\n");
        printf("4. ���� �ùķ��̼� ���� (peek)\n");
        printf("0. ����\n");
        printf("����: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("���α׷��� �����մϴ�.\n");
                exit(0);

            case 1:
                if (is_full()) {
                    printf("ť�� ���� á���ϴ�. ���� ���� �ùķ��̼��� ������ּ���.\n");
                } else {
                    Element elem = input_simulation_data();
                    enqueue(elem);
                    printf("�ùķ��̼��� ť�� �߰��Ǿ����ϴ�.\n");
                }
                break;

            case 2:
                if (is_empty()) {
                    printf("ť�� ����ֽ��ϴ�. ���� �ùķ��̼��� �߰����ּ���.\n");
                } else {
                    Element elem = dequeue();
                    printf("ť���� �ùķ��̼��� ������ ����մϴ�.\n");
                    calculate_decay(elem);
                }
                break;

            case 3:
                if (is_empty()) {
                    printf("ť�� ����ֽ��ϴ�.\n");
                } else {
                    print_queue("���� ť ����:");
                }
                break;

            case 4:
                if (is_empty()) {
                    printf("ť�� ����ֽ��ϴ�.\n");
                } else {
                    Element elem = peek();
                    printf("���� ó���� �ùķ��̼�: �ʱⷮ=%.6fg, �ر����=%.8f/��, �ð�=%.2f��\n",
                           elem.initialAmount, elem.decayConstant, elem.time);
                }
                break;

            default:
                printf("�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n");
        }
    }

    return 0;
}