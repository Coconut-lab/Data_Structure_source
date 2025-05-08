// ���� ���� �˰��� ����
// �ð� ���⵵ : O(n^2)
// ���� ���⵵ : O(1)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// �� ������ ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ���� ���� �Լ�
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    
    // �迭�� ��� ��Ҹ� ��ȸ
    for (i = 0; i < n - 1; i++) {
        // ���� ��ġ���� ���� ���� ����� �ε��� ã��
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // ã�� �ּҰ��� ���� ��ġ�� ��ȯ
        swap(&arr[min_idx], &arr[i]);
    }
}

// �迭 ��� �Լ�
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("���� �� �迭: \n");
    printArray(arr, n);
    
    selectionSort(arr, n);
    
    printf("���� ���� �� �迭: \n");
    printArray(arr, n);
    
    return 0;
}