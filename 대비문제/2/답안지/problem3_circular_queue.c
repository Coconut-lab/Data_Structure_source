// ���� 3: ���� ť ���� (������� ���)
// QueueStruct.h�� ����Ͽ� �迭 ��� ���� ť ����

#include <stdio.h>
#include <stdlib.h>
#include "QueueStruct.h"

// ť�� �迭ó�� �����ϴ� �Լ� (index��° ���� ��ȯ)
Element queue_get_at(Queue* q, int index) {
    if (is_empty(q) || index < 0 || index >= size(q)) {
        printf("�߸��� �ε����Դϴ�! (�ε���: %d, ť ũ��: %d)\n", index, size(q));
        return -1;
    }
    
    // front���� �����ؼ� index��ŭ �̵��� ��ġ ���
    int actual_index = (q->front + 1 + index) % MAX_SIZE;
    return q->data[actual_index];
}

// ť�� ù ��° ���� Ȯ�� (�������� ����)
Element queue_front(Queue* q) {
    if (is_empty(q)) {
        printf("ť�� ����ֽ��ϴ�!\n");
        return -1;
    }
    return peek(q);  // QueueStruct.h�� peek �Լ� ���
}

// ť�� ������ ���� Ȯ�� (�������� ����)
Element queue_rear(Queue* q) {
    if (is_empty(q)) {
        printf("ť�� ����ֽ��ϴ�!\n");
        return -1;
    }
    return q->data[q->rear];
}

// ť ��ü ���
void print_queue(Queue* q) {
    if (is_empty(q)) {
        printf("ť�� ����ֽ��ϴ�.\n");
        return;
    }
    
    printf("[");
    int queue_size = size(q);
    
    for (int i = 0; i < queue_size; i++) {
        int index = (q->front + 1 + i) % MAX_SIZE;
        printf("%d", q->data[index]);
        if (i < queue_size - 1) printf(", ");
    }
    
    printf("] (ũ��: %d)\n", queue_size);
}

// ť�� ��� ���� ����
void clear_queue(Queue* q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
}

// ť ���� ���� ���
void print_queue_info(Queue* q) {
    printf("ť ���� - ũ��: %d, front: %d, rear: %d\n", 
           size(q), q->front, q->rear);
}

// �׽�Ʈ �Լ�
void test_circular_queue() {
    Queue q;  // QueueStruct.h�� Queue ����ü ���
    init_queue(&q);  // QueueStruct.h�� �ʱ�ȭ �Լ� ���
    
    // 1,2,3,4,5 ������ enqueue
    for (int i = 1; i <= 5; i++) {
        enqueue(&q, i);  // QueueStruct.h�� enqueue ���
    }
    printf("�ʱ� ����: ");
    print_queue(&q);
    
    // dequeue 2��
    dequeue(&q);  // QueueStruct.h�� dequeue ���
    dequeue(&q);
    printf("2�� ���� ��: ");
    print_queue(&q);
    
    // 6,7 �߰�
    enqueue(&q, 6);
    enqueue(&q, 7);
    printf("���� ����: ");
    print_queue(&q);
    
    // ���� �䱸���� �׽�Ʈ
    printf("queue_get_at(1) = %d\n", queue_get_at(&q, 1));
    
    // �߰� �׽�Ʈ
    printf("\n=== �߰� ��� �׽�Ʈ ===\n");
    printf("front ����: %d\n", queue_front(&q));
    printf("rear ����: %d\n", queue_rear(&q));
    print_queue_info(&q);
    
    // �ε��� ���� �׽�Ʈ
    printf("\n�ε����� ����:\n");
    for (int i = 0; i < size(&q); i++) {
        printf("index %d: %d\n", i, queue_get_at(&q, i));
    }
    
    clear_queue(&q);
    printf("\n���� ��: ");
    print_queue(&q);
}

int main() {
    test_circular_queue();
    return 0;
}
