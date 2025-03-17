#include "total_code-1-1-head.h"

int main(void) {
    int menu;
    clock_t start, finish;
    double  duration;

    while (1) {
        main_screen();

        printf(">> 메뉴 선택: ");
        scanf("%d", &menu);

        if (menu == 1) {
            int n;

            print_line();
            printf("n개 합 구 하 기\n");
            printf("\nn의 값을 입력하세요: ");
            scanf("%d", &n);

            start = clock();
            printf("1부터 %d까지의 합은 %d입니다.\n", n, calc_sum(n));
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n소요 시간: %lf초\n", duration);
            print_line();
        } else if (menu == 2) {
            int a, b, c;
            int max;

            print_line();
            printf("최 대 값 찾 기\n");
            printf("\n세 개의 정수를 입력하세요: ");
            scanf("%d %d %d", &a, &b, &c);

            start = clock();
            max = find_max(a, b, c);
            printf("최댓값 = %d\n", max);
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n소요 시간: %lf초\n", duration);
            print_line();
        } else if (menu == 3) {
            int a[8] = { 32, 14, 5, 17, 23, 9, 11, 4 };
            int b[8] = { 32, 14, 5, 17, 23, 14, 11, 4 };

            print_line();
            printf("중 복 요 소 찾 기\n");

            start = clock();
            printf("A: 중복된 요소 %s\n", has_duplicate_elem(a, 8) ? "있음" : "없음");
            printf("B: 중복된 요소 %s\n", has_duplicate_elem(b, 8) ? "있음" : "없음");
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n소요 시간: %lf초\n", duration);
            print_line();
        } else if (menu == 4) {
            int arr[10] = { 5, 9, 10, 17, 21, 29, 33, 37, 38, 43 };
            int index;

            print_line();
            printf("순 차 탐 색\n");

            start = clock();
            index = sequential_search(arr, 10, 5);
            printf(" 5의 위치 = %d\n", index);
            index = sequential_search(arr, 10, 43);
            printf("43의 위치 = %d\n", index);
            index = sequential_search(arr, 10, 42);
            printf("42의 위치 = %d\n", index);
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n소요 시간: %lf초\n", duration);
            print_line();
        } else if (menu == 5) {
            return 0;
        } else {
            printf("잘못된 메뉴 선택입니다.\n");
        }
    }
}