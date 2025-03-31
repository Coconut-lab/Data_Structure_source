#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// �ִ�����(GCD) ��� �Լ� - ��Ŭ���� �˰��� ���
int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// �ּҰ����(LCM) ��� �Լ� - LCM = (a * b) / GCD(a, b)
int calculateLCM(int a, int b) {
    return (a * b) / calculateGCD(a, b);
}

// ���μ� ���� �Լ�
void primeFactorization(int num, FILE *file) {
    fprintf(file, "%d�� ���μ� ����: ", num);

    // ���μ����� ����
    int factor = 2;
    int first = 1; // ù ��° �μ����� Ȯ�ο�

    while (num > 1) {
        int count = 0;

        while (num % factor == 0) {
            count++;
            num /= factor;
        }

        if (count > 0) {
            if (!first) {
                fprintf(file, " �� ");
            } else {
                first = 0;
            }

            if (count == 1) {
                fprintf(file, "%d", factor);
            } else {
                fprintf(file, "%d^%d", factor, count);
            }
        }

        factor++;

        // ���� ����ȭ: ���� num�� �Ҽ���� �ݺ� �ߴ�
        if (factor * factor > num && num > 1) {
            if (!first) {
                fprintf(file, " �� ");
            }
            fprintf(file, "%d", num);
            break;
        }
    }

    fprintf(file, "\n");
}

// ��ǥ ����ü
typedef struct {
    int x;
    int y;
} Point;

// ������ ���� ���
double calculateSlope(Point p1, Point p2) {
    return (double)(p2.y - p1.y) / (p2.x - p1.x);
}

// ��ǥ ���� �Լ� (GCD, LCM ���� Ȱ��)
Point predictPoint(int gcd, int lcm) {
    Point result;
    result.x = lcm / gcd;  // ���⿡ ����� x ��ǥ ����
    result.y = lcm / (lcm / gcd);  // y = x / ����
    return result;
}

int main() {
    // ���� ����
    FILE *outputFile = fopen("gcd_lcm_results.txt", "w");
    if (outputFile == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ����ڷκ��� �� ���� �Է� �ޱ�
    int num1, num2;
    printf("ù ��° ���ڸ� �Է��ϼ���: ");
    scanf("%d", &num1);
    printf("�� ��° ���ڸ� �Է��ϼ���: ");
    scanf("%d", &num2);

    // �Է°� ���Ͽ� ����
    fprintf(outputFile, "�Է� ���� ����: %d, %d\n\n", num1, num2);

    // ���μ� ����
    fprintf(outputFile, "1. ���μ� ����\n");
    primeFactorization(num1, outputFile);
    primeFactorization(num2, outputFile);
    fprintf(outputFile, "\n");

    // GCD�� LCM ���
    int gcd = calculateGCD(num1, num2);
    int lcm = calculateLCM(num1, num2);

    fprintf(outputFile, "2. GCD�� LCM ���\n");
    fprintf(outputFile, "GCD(%d, %d) = %d\n", num1, num2, gcd);
    fprintf(outputFile, "LCM(%d, %d) = %d\n", num1, num2, lcm);
    fprintf(outputFile, "GCD �� LCM = %d �� %d = %d\n", gcd, lcm, gcd * lcm);
    fprintf(outputFile, "num1 �� num2 = %d �� %d = %d\n", num1, num2, num1 * num2);
    fprintf(outputFile, "\n");

    // ����: ��ǥ��� �м� (�־��� ���ÿ� ����)
    fprintf(outputFile, "3. ��ǥ��� �м�\n");

    // �⺻ ��ǥ�� ���� (ȭ��Ʈ���� �̹��� ����)
    Point p1 = {2, 1};
    Point p2 = {10, 5};
    Point p3 = {30, 15};

    // ���� ���
    double slope1 = calculateSlope(p1, p2);
    double slope2 = calculateSlope(p2, p3);

    fprintf(outputFile, "��ǥ��: (2, 1), (10, 5), (30, 15)\n");
    fprintf(outputFile, "����1 (��1-��2): %.2f\n", slope1);
    fprintf(outputFile, "����2 (��2-��3): %.2f\n", slope2);

    // GCD, LCM�� �̿��� ����
    fprintf(outputFile, "\nGCD�� LCM�� Ȱ���� ����:\n");
    fprintf(outputFile, "GCD = %d, LCM = %d\n", gcd, lcm);

    Point predicted = predictPoint(gcd, lcm);
    fprintf(outputFile, "���� ��ǥ: (%d, %d)\n", predicted.x, predicted.y);

    // �ܼ� ���
    printf("\n����� �Ϸ�Ǿ����ϴ�.\n");
    printf("GCD(%d, %d) = %d\n", num1, num2, gcd);
    printf("LCM(%d, %d) = %d\n", num1, num2, lcm);
    printf("����� 'gcd_lcm_results.txt' ���Ͽ� ����Ǿ����ϴ�.\n");

    fclose(outputFile);
    return 0;
}