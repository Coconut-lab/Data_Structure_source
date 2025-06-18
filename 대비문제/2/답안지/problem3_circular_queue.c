// 문제 3: 원형 큐 구현 (헤더파일 사용)
// QueueStruct.h를 사용하여 배열 기반 원형 큐 구현

#include <stdio.h>
#include <stdlib.h>
#include "QueueStruct.h"

// 큐를 배열처럼 접근하는 함수 (index번째 원소 반환)
Element queue_get_at(Queue* q, int index) {
    if (is_empty(q) || index < 0 || index >= size(q)) {
        printf("잘못된 인덱스입니다! (인덱스: %d, 큐 크기: %d)\n", index, size(q));
        return -1;
    }
    
    // front부터 시작해서 index만큼 이동한 위치 계산
    int actual_index = (q->front + 1 + index) % MAX_SIZE;
    return q->data[actual_index];
}

// 큐의 첫 번째 원소 확인 (제거하지 않음)
Element queue_front(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어있습니다!\n");
        return -1;
    }
    return peek(q);  // QueueStruct.h의 peek 함수 사용
}

// 큐의 마지막 원소 확인 (제거하지 않음)
Element queue_rear(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어있습니다!\n");
        return -1;
    }
    return q->data[q->rear];
}

// 큐 전체 출력
void print_queue(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어있습니다.\n");
        return;
    }
    
    printf("[");
    int queue_size = size(q);
    
    for (int i = 0; i < queue_size; i++) {
        int index = (q->front + 1 + i) % MAX_SIZE;
        printf("%d", q->data[index]);
        if (i < queue_size - 1) printf(", ");
    }
    
    printf("] (크기: %d)\n", queue_size);
}

// 큐의 모든 원소 제거
void clear_queue(Queue* q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
}

// 큐 상태 정보 출력
void print_queue_info(Queue* q) {
    printf("큐 정보 - 크기: %d, front: %d, rear: %d\n", 
           size(q), q->front, q->rear);
}

// 테스트 함수
void test_circular_queue() {
    Queue q;  // QueueStruct.h의 Queue 구조체 사용
    init_queue(&q);  // QueueStruct.h의 초기화 함수 사용
    
    // 1,2,3,4,5 순서로 enqueue
    for (int i = 1; i <= 5; i++) {
        enqueue(&q, i);  // QueueStruct.h의 enqueue 사용
    }
    printf("초기 상태: ");
    print_queue(&q);
    
    // dequeue 2번
    dequeue(&q);  // QueueStruct.h의 dequeue 사용
    dequeue(&q);
    printf("2개 제거 후: ");
    print_queue(&q);
    
    // 6,7 추가
    enqueue(&q, 6);
    enqueue(&q, 7);
    printf("최종 상태: ");
    print_queue(&q);
    
    // 문제 요구사항 테스트
    printf("queue_get_at(1) = %d\n", queue_get_at(&q, 1));
    
    // 추가 테스트
    printf("\n=== 추가 기능 테스트 ===\n");
    printf("front 원소: %d\n", queue_front(&q));
    printf("rear 원소: %d\n", queue_rear(&q));
    print_queue_info(&q);
    
    // 인덱스 접근 테스트
    printf("\n인덱스별 원소:\n");
    for (int i = 0; i < size(&q); i++) {
        printf("index %d: %d\n", i, queue_get_at(&q, i));
    }
    
    clear_queue(&q);
    printf("\n정리 후: ");
    print_queue(&q);
}

int main() {
    test_circular_queue();
    return 0;
}
