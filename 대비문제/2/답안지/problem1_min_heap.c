// ���� 1: �ּ� ��(Min Heap) ����
// MaxHeap.c�� �����Ͽ� �ּҰ��� ��Ʈ�� ���� �� ����

#include <stdio.h>
#include <stdlib.h>

#define MAX_HSIZE 100
#define PARENT(i) (i/2)     // �θ� ��� �ε���
#define LEFT(i) (i*2)       // ���� �ڽ� �ε���  
#define RIGHT(i) (i*2+1)    // ������ �ڽ� �ε���

typedef int MinHNode;
MinHNode minHeap[MAX_HSIZE];    // �ּ� �� �迭
int min_heap_size = 0;          // ���� �� ũ��

// �� �ʱ�ȭ
void init_min_heap() {
    min_heap_size = 0;
}

// ���� ����ִ��� Ȯ��
int is_empty_min_heap() {
    return min_heap_size == 0;
}

// ���� ���� á���� Ȯ��
int is_full_min_heap() {
    return (min_heap_size == MAX_HSIZE - 1);
}

// �ּҰ� Ȯ�� (��Ʈ ����)
MinHNode min_heap_peek() {
    return minHeap[1];
}

// �ּ� ���� ���� ����
// MaxHeap�� �ٸ� ��: �θ𺸴� ������ ���� �ö�
void min_heap_push(MinHNode n) {
    if (is_full_min_heap()) {
        printf("���� ���� á���ϴ�.\n");
        return;
    }
    
    min_heap_size += 1;             // ũ�� ����
    minHeap[min_heap_size] = n;     // ������ ��ġ�� ����
    int i = min_heap_size;          // ���� ��ġ
    
    // �θ�� ���ϸ鼭 ���� �̵� (�ּ� ���̹Ƿ� ���� ���� ����)
    while (i != 1) {
        if (minHeap[i] < minHeap[PARENT(i)]) {  // �θ𺸴� ������
            // �θ�� ��ȯ
            MinHNode temp = minHeap[i];
            minHeap[i] = minHeap[PARENT(i)];
            minHeap[PARENT(i)] = temp;
            i = PARENT(i);              // �� ���� ����
        }
        else break;                     // �ùٸ� ��ġ ã��
    }
}

// �ּ� ������ �ּҰ� ����
MinHNode min_heap_pop() {
    if (is_empty_min_heap()) {
        printf("���� ����ֽ��ϴ�.\n");
        return -1;
    }
    
    MinHNode root = minHeap[1];         // �ּҰ� ����
    MinHNode last = minHeap[min_heap_size];  // ������ ����
    minHeap[1] = last;                  // ������ ���Ҹ� ��Ʈ�� �̵�
    min_heap_size -= 1;                 // ũ�� ����
    
    int i = 1;                          // ��Ʈ���� �Ʒ��� �̵�
    
    // �ڽİ� ���ϸ鼭 �Ʒ��� �̵�
    while (LEFT(i) <= min_heap_size) {
        int child;
        
        // �� ���� �ڽ��� ���� (�ּ� ���̹Ƿ�)
        if (RIGHT(i) <= min_heap_size) {
            child = (minHeap[LEFT(i)] < minHeap[RIGHT(i)]) ? LEFT(i) : RIGHT(i);
        } else {
            child = LEFT(i);
        }
        
        if (minHeap[i] <= minHeap[child]) break;  // �ùٸ� ��ġ
        
        // �� ���� �ڽİ� ��ȯ
        MinHNode temp = minHeap[i];
        minHeap[i] = minHeap[child];
        minHeap[child] = temp;
        i = child;                      // �� ���� �Ʒ���
    }
    
    return root;
}

// k��° ���� ���� ã�� (�� ���� ����)
// ���: �ӽ� �迭�� k�� pop�� �� �ٽ� push
MinHNode find_kth_smallest(int k) {
    if (k > min_heap_size || k <= 0) {
        printf("�߸��� k���Դϴ�.\n");
        return -1;
    }
    
    // ���� �� ���
    MinHNode backup[MAX_HSIZE];
    int backup_size = min_heap_size;
    for (int i = 1; i <= min_heap_size; i++) {
        backup[i] = minHeap[i];
    }
    
    MinHNode result;
    MinHNode temp[k];
    
    // k��°���� pop�Ͽ� ����
    for (int i = 0; i < k; i++) {
        temp[i] = min_heap_pop();
        if (i == k-1) result = temp[i];  // k��° ����
    }
    
    // ���� �� ����
    min_heap_size = backup_size;
    for (int i = 1; i <= backup_size; i++) {
        minHeap[i] = backup[i];
    }
    
    return result;
}

// �� ��� �Լ�
void print_min_heap() {
    printf("MinHeap: ");
    for (int i = 1; i <= min_heap_size; i++) {
        printf("%2d ", minHeap[i]);
    }
    printf("\n");
}

// �׽�Ʈ �Լ�
void test_min_heap() {
    int data[] = {8, 3, 5, 4, 7, 6, 9, 2, 1};
    int n = sizeof(data) / sizeof(data[0]);
    
    init_min_heap();
    
    // ���� �׽�Ʈ
    for (int i = 0; i < n; i++) {
        min_heap_push(data[i]);
    }
    printf("���� �Ϸ�: ");
    print_min_heap();
    
    // k��° ���� ���� ã��
    printf("3��° ���� ����: %d\n", find_kth_smallest(3));
    
    // ���ĵ� ������ ���
    printf("���� ���: ");
    while (!is_empty_min_heap()) {
        printf("%d ", min_heap_pop());
    }
    printf("\n");
}

int main() {
    test_min_heap();
    return 0;
}
