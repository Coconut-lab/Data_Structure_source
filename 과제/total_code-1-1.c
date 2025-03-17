#include "total_code-1-1-head.h"

int main(void) {
    int menu;
    clock_t start, finish;
    double  duration;

    while (1) {
        main_screen();

        printf(">> �޴� ����: ");
        scanf("%d", &menu);

        if (menu == 1) {
            int n;

            print_line();
            printf("n�� �� �� �� ��\n");
            printf("\nn�� ���� �Է��ϼ���: ");
            scanf("%d", &n);

            start = clock();
            printf("1���� %d������ ���� %d�Դϴ�.\n", n, calc_sum(n));
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n�ҿ� �ð�: %lf��\n", duration);
            print_line();
        } else if (menu == 2) {
            int a, b, c;
            int max;

            print_line();
            printf("�� �� �� ã ��\n");
            printf("\n�� ���� ������ �Է��ϼ���: ");
            scanf("%d %d %d", &a, &b, &c);

            start = clock();
            max = find_max(a, b, c);
            printf("�ִ� = %d\n", max);
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n�ҿ� �ð�: %lf��\n", duration);
            print_line();
        } else if (menu == 3) {
            int a[8] = { 32, 14, 5, 17, 23, 9, 11, 4 };
            int b[8] = { 32, 14, 5, 17, 23, 14, 11, 4 };

            print_line();
            printf("�� �� �� �� ã ��\n");

            start = clock();
            printf("A: �ߺ��� ��� %s\n", has_duplicate_elem(a, 8) ? "����" : "����");
            printf("B: �ߺ��� ��� %s\n", has_duplicate_elem(b, 8) ? "����" : "����");
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n�ҿ� �ð�: %lf��\n", duration);
            print_line();
        } else if (menu == 4) {
            int arr[10] = { 5, 9, 10, 17, 21, 29, 33, 37, 38, 43 };
            int index;

            print_line();
            printf("�� �� Ž ��\n");

            start = clock();
            index = sequential_search(arr, 10, 5);
            printf(" 5�� ��ġ = %d\n", index);
            index = sequential_search(arr, 10, 43);
            printf("43�� ��ġ = %d\n", index);
            index = sequential_search(arr, 10, 42);
            printf("42�� ��ġ = %d\n", index);
            finish = clock();

            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("\n�ҿ� �ð�: %lf��\n", duration);
            print_line();
        } else if (menu == 5) {
            return 0;
        } else {
            printf("�߸��� �޴� �����Դϴ�.\n");
        }
    }
}