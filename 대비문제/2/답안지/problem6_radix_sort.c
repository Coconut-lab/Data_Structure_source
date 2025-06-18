// 문제 6: 기수 정렬(Radix Sort) 구현 - 간소화 버전
// sort_all.c의 정렬 구조를 참고하여 기수 정렬 구현

#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 10
#define BASE 10

void print_array(int arr[], int n, char* msg) {
    printf("%s: ", msg);
    for (int i = 0; i < n; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n");
}

int find_max(int A[], int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    return max;
}

int get_digit(int number, int position) {
    int divisor = 1;
    for (int i = 0; i < position; i++) {
        divisor *= 10;
    }
    return (number / divisor) % 10;
}

void counting_sort_by_digit(int A[], int n, int digit_pos) {
    int output[n];
    int count[BASE] = {0};
    
    // 빈도수 계산
    for (int i = 0; i < n; i++) {
        int digit = get_digit(A[i], digit_pos);
        count[digit]++;
    }
    
    // 누적 빈도수 계산
    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }
    
    // 안정 정렬 수행
    for (int i = n - 1; i >= 0; i--) {
        int digit = get_digit(A[i], digit_pos);
        output[count[digit] - 1] = A[i];
        count[digit]--;
    }
    
    // 결과 복사
    for (int i = 0; i < n; i++) {
        A[i] = output[i];
    }
}

void radix_sort(int A[], int n) {
    int max_value = find_max(A, n);
    int digit_pos = 0;
    
    while (max_value > 0) {
        counting_sort_by_digit(A, n, digit_pos);
        max_value /= 10;
        digit_pos++;
    }
}

void radix_sort_with_negative(int A[], int n) {
    int positive[n], negative[n];
    int pos_count = 0, neg_count = 0;
    
    // 양수와 음수 분리
    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            positive[pos_count++] = A[i];
        } else {
            negative[neg_count++] = -A[i];
        }
    }
    
    // 각각 정렬
    if (pos_count > 0) {
        radix_sort(positive, pos_count);
    }
    if (neg_count > 0) {
        radix_sort(negative, neg_count);
    }
    
    // 결과 합치기
    int index = 0;
    for (int i = neg_count - 1; i >= 0; i--) {
        A[index++] = -negative[i];
    }
    for (int i = 0; i < pos_count; i++) {
        A[index++] = positive[i];
    }
}

void test_radix_sort() {
    // 기본 테스트
    int test1[] = {170, 45, 75, 90, 2, 802, 24, 66};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    
    print_array(test1, n1, "정렬 전");
    radix_sort(test1, n1);
    print_array(test1, n1, "정렬 후");
    
    // 음수 포함 테스트
    int test2[] = {-45, 170, -2, 90, 24, -802, 66};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    
    printf("\n");
    print_array(test2, n2, "음수 포함 정렬 전");
    radix_sort_with_negative(test2, n2);
    print_array(test2, n2, "음수 포함 정렬 후");
}

int main() {
    test_radix_sort();
    return 0;
}
