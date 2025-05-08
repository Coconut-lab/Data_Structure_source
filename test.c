#include <stdio.h>

void maxSubArraySum(int arr[], int n) {
    int max_so_far = arr[0];       // 지금까지의 최대 합
    int max_ending_here = arr[0];  // 현재 위치에서 끝나는 부분 배열의 최대 합

    // 최대 부분 배열의 시작과 끝 인덱스를 추적
    int start = 0;
    int end = 0;
    int s = 0;  // 현재 부분 배열의 시작 인덱스

    for (int i = 1; i < n; i++) {
        // 새로 시작하는 것이 더 나은 경우
        if (arr[i] > max_ending_here + arr[i]) {
            max_ending_here = arr[i];
            s = i;  // 새로운 시작 인덱스
        }
        // 기존 부분 배열에 현재 요소를 추가하는 경우
        else {
            max_ending_here = max_ending_here + arr[i];
        }

        // 전체 최대값 갱신
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
    }

    // 최대 부분 배열과 합 출력
    printf("최대 부분 배열 합: %d\n", max_so_far);
    printf("최대 부분 배열: [");
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
    printf("배열의 크기를 입력하세요: ");
    scanf("%d", &n);

    int arr[100];  // 문제 제한 n ≤ 100

    printf("%d개의 정수를 입력하세요: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    maxSubArraySum(arr, n);

    return 0;
}