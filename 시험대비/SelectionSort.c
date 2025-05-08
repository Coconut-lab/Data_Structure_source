// 선택 정렬 알고리즘 구현
// 시간 복잡도 : O(n^2)
// 공간 복잡도 : O(1)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 두 정수를 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 선택 정렬 함수
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    
    // 배열의 모든 요소를 순회
    for (i = 0; i < n - 1; i++) {
        // 현재 위치부터 가장 작은 요소의 인덱스 찾기
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // 찾은 최소값을 현재 위치와 교환
        swap(&arr[min_idx], &arr[i]);
    }
}

// 배열 출력 함수
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
    
    printf("정렬 전 배열: \n");
    printArray(arr, n);
    
    selectionSort(arr, n);
    
    printf("선택 정렬 후 배열: \n");
    printArray(arr, n);
    
    return 0;
}