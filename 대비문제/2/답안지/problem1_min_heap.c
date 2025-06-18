// 문제 1: 최소 힙(Min Heap) 구현
// MaxHeap.c를 참고하여 최소값이 루트에 오는 힙 구현

#include <stdio.h>
#include <stdlib.h>

#define MAX_HSIZE 100
#define PARENT(i) (i/2)     // 부모 노드 인덱스
#define LEFT(i) (i*2)       // 왼쪽 자식 인덱스  
#define RIGHT(i) (i*2+1)    // 오른쪽 자식 인덱스

typedef int MinHNode;
MinHNode minHeap[MAX_HSIZE];    // 최소 힙 배열
int min_heap_size = 0;          // 현재 힙 크기

// 힙 초기화
void init_min_heap() {
    min_heap_size = 0;
}

// 힙이 비어있는지 확인
int is_empty_min_heap() {
    return min_heap_size == 0;
}

// 힙이 가득 찼는지 확인
int is_full_min_heap() {
    return (min_heap_size == MAX_HSIZE - 1);
}

// 최소값 확인 (루트 원소)
MinHNode min_heap_peek() {
    return minHeap[1];
}

// 최소 힙에 원소 삽입
// MaxHeap과 다른 점: 부모보다 작으면 위로 올라감
void min_heap_push(MinHNode n) {
    if (is_full_min_heap()) {
        printf("힙이 가득 찼습니다.\n");
        return;
    }
    
    min_heap_size += 1;             // 크기 증가
    minHeap[min_heap_size] = n;     // 마지막 위치에 삽입
    int i = min_heap_size;          // 현재 위치
    
    // 부모와 비교하면서 위로 이동 (최소 힙이므로 작은 값이 위로)
    while (i != 1) {
        if (minHeap[i] < minHeap[PARENT(i)]) {  // 부모보다 작으면
            // 부모와 교환
            MinHNode temp = minHeap[i];
            minHeap[i] = minHeap[PARENT(i)];
            minHeap[PARENT(i)] = temp;
            i = PARENT(i);              // 한 레벨 위로
        }
        else break;                     // 올바른 위치 찾음
    }
}

// 최소 힙에서 최소값 제거
MinHNode min_heap_pop() {
    if (is_empty_min_heap()) {
        printf("힙이 비어있습니다.\n");
        return -1;
    }
    
    MinHNode root = minHeap[1];         // 최소값 저장
    MinHNode last = minHeap[min_heap_size];  // 마지막 원소
    minHeap[1] = last;                  // 마지막 원소를 루트로 이동
    min_heap_size -= 1;                 // 크기 감소
    
    int i = 1;                          // 루트부터 아래로 이동
    
    // 자식과 비교하면서 아래로 이동
    while (LEFT(i) <= min_heap_size) {
        int child;
        
        // 더 작은 자식을 선택 (최소 힙이므로)
        if (RIGHT(i) <= min_heap_size) {
            child = (minHeap[LEFT(i)] < minHeap[RIGHT(i)]) ? LEFT(i) : RIGHT(i);
        } else {
            child = LEFT(i);
        }
        
        if (minHeap[i] <= minHeap[child]) break;  // 올바른 위치
        
        // 더 작은 자식과 교환
        MinHNode temp = minHeap[i];
        minHeap[i] = minHeap[child];
        minHeap[child] = temp;
        i = child;                      // 한 레벨 아래로
    }
    
    return root;
}

// k번째 작은 원소 찾기 (힙 구조 유지)
// 방법: 임시 배열에 k번 pop한 후 다시 push
MinHNode find_kth_smallest(int k) {
    if (k > min_heap_size || k <= 0) {
        printf("잘못된 k값입니다.\n");
        return -1;
    }
    
    // 원본 힙 백업
    MinHNode backup[MAX_HSIZE];
    int backup_size = min_heap_size;
    for (int i = 1; i <= min_heap_size; i++) {
        backup[i] = minHeap[i];
    }
    
    MinHNode result;
    MinHNode temp[k];
    
    // k번째까지 pop하여 저장
    for (int i = 0; i < k; i++) {
        temp[i] = min_heap_pop();
        if (i == k-1) result = temp[i];  // k번째 원소
    }
    
    // 원본 힙 복원
    min_heap_size = backup_size;
    for (int i = 1; i <= backup_size; i++) {
        minHeap[i] = backup[i];
    }
    
    return result;
}

// 힙 출력 함수
void print_min_heap() {
    printf("MinHeap: ");
    for (int i = 1; i <= min_heap_size; i++) {
        printf("%2d ", minHeap[i]);
    }
    printf("\n");
}

// 테스트 함수
void test_min_heap() {
    int data[] = {8, 3, 5, 4, 7, 6, 9, 2, 1};
    int n = sizeof(data) / sizeof(data[0]);
    
    init_min_heap();
    
    // 삽입 테스트
    for (int i = 0; i < n; i++) {
        min_heap_push(data[i]);
    }
    printf("삽입 완료: ");
    print_min_heap();
    
    // k번째 작은 원소 찾기
    printf("3번째 작은 원소: %d\n", find_kth_smallest(3));
    
    // 정렬된 순서로 출력
    printf("정렬 결과: ");
    while (!is_empty_min_heap()) {
        printf("%d ", min_heap_pop());
    }
    printf("\n");
}

int main() {
    test_min_heap();
    return 0;
}
