#include <stdio.h>

void maxSubArraySum(int arr[], int n) {
    int max_so_far = arr[0];       // ���ݱ����� �ִ� ��
    int max_ending_here = arr[0];  // ���� ��ġ���� ������ �κ� �迭�� �ִ� ��

    // �ִ� �κ� �迭�� ���۰� �� �ε����� ����
    int start = 0;
    int end = 0;
    int s = 0;  // ���� �κ� �迭�� ���� �ε���

    for (int i = 1; i < n; i++) {
        // ���� �����ϴ� ���� �� ���� ���
        if (arr[i] > max_ending_here + arr[i]) {
            max_ending_here = arr[i];
            s = i;  // ���ο� ���� �ε���
        }
        // ���� �κ� �迭�� ���� ��Ҹ� �߰��ϴ� ���
        else {
            max_ending_here = max_ending_here + arr[i];
        }

        // ��ü �ִ밪 ����
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
    }

    // �ִ� �κ� �迭�� �� ���
    printf("�ִ� �κ� �迭 ��: %d\n", max_so_far);
    printf("�ִ� �κ� �迭: [");
    for (int i = start; i <= end; i++) {
        printf("%d", arr[i]);
        if (i < end) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int n;
    printf("�迭�� ũ�⸦ �Է��ϼ���: ");
    scanf("%d", &n);

    int arr[100];  // ���� ���� n �� 100

    printf("%d���� ������ �Է��ϼ���: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    maxSubArraySum(arr, n);

    return 0;
}