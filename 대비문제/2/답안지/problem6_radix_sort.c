// ���� 6: ��� ����(Radix Sort) ���� - ����ȭ ����
// sort_all.c�� ���� ������ �����Ͽ� ��� ���� ����

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
    
    // �󵵼� ���
    for (int i = 0; i < n; i++) {
        int digit = get_digit(A[i], digit_pos);
        count[digit]++;
    }
    
    // ���� �󵵼� ���
    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }
    
    // ���� ���� ����
    for (int i = n - 1; i >= 0; i--) {
        int digit = get_digit(A[i], digit_pos);
        output[count[digit] - 1] = A[i];
        count[digit]--;
    }
    
    // ��� ����
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
    
    // ����� ���� �и�
    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            positive[pos_count++] = A[i];
        } else {
            negative[neg_count++] = -A[i];
        }
    }
    
    // ���� ����
    if (pos_count > 0) {
        radix_sort(positive, pos_count);
    }
    if (neg_count > 0) {
        radix_sort(negative, neg_count);
    }
    
    // ��� ��ġ��
    int index = 0;
    for (int i = neg_count - 1; i >= 0; i--) {
        A[index++] = -negative[i];
    }
    for (int i = 0; i < pos_count; i++) {
        A[index++] = positive[i];
    }
}

void test_radix_sort() {
    // �⺻ �׽�Ʈ
    int test1[] = {170, 45, 75, 90, 2, 802, 24, 66};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    
    print_array(test1, n1, "���� ��");
    radix_sort(test1, n1);
    print_array(test1, n1, "���� ��");
    
    // ���� ���� �׽�Ʈ
    int test2[] = {-45, 170, -2, 90, 24, -802, 66};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    
    printf("\n");
    print_array(test2, n2, "���� ���� ���� ��");
    radix_sort_with_negative(test2, n2);
    print_array(test2, n2, "���� ���� ���� ��");
}

int main() {
    test_radix_sort();
    return 0;
}
