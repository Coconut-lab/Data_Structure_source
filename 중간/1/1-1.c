#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// ������ ����Ʈ ����ü
typedef struct {
    double x;
    double y;
} Point;

// �����Լ� ����� �����ϴ� ����ü
typedef struct {
    double a;  // x^2 ���
    double b;  // x ���
    double c;  // �����
} QuadraticFunction;

// �����Լ� ���� �Լ� (�ּ�������)
QuadraticFunction fitQuadratic(Point* points, int n) {
    // ���� ������ �ý��� ������ ���� �հ� ����
    double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0, sum_xy = 0, sum_x2y = 0;

    // �հ� ���
    for (int i = 0; i < n; i++) {
        double x = points[i].x;
        double y = points[i].y;

        sum_x += x;
        sum_y += y;
        sum_x2 += x * x;
        sum_x3 += x * x * x;
        sum_x4 += x * x * x * x;
        sum_xy += x * y;
        sum_x2y += x * x * y;
    }

    // ���������� �ذ� (��Ľ� ���)
    // a(sum_x4) + b(sum_x3) + c(sum_x2) = sum_x2y
    // a(sum_x3) + b(sum_x2) + c(sum_x) = sum_xy
    // a(sum_x2) + b(sum_x) + c(n) = sum_y

    double D = sum_x4 * (sum_x2 * n - sum_x * sum_x) -
               sum_x3 * (sum_x3 * n - sum_x * sum_x2) +
               sum_x2 * (sum_x3 * sum_x - sum_x2 * sum_x2);

    double Da = sum_x2y * (sum_x2 * n - sum_x * sum_x) -
                sum_xy * (sum_x3 * n - sum_x * sum_x2) +
                sum_y * (sum_x3 * sum_x - sum_x2 * sum_x2);

    double Db = sum_x4 * (sum_xy * n - sum_y * sum_x) -
                sum_x2y * (sum_x3 * n - sum_x * sum_x2) +
                sum_x2 * (sum_x3 * sum_y - sum_x2 * sum_xy);

    double Dc = sum_x4 * (sum_x2 * sum_y - sum_x * sum_xy) -
                sum_x3 * (sum_x3 * sum_y - sum_x * sum_x2y) +
                sum_x2y * (sum_x3 * sum_x - sum_x2 * sum_x2);

    QuadraticFunction result;
    result.a = Da / D;
    result.b = Db / D;
    result.c = Dc / D;

    return result;
}

// �־��� x�� ���� �����Լ� �� ���
double evaluateQuadratic(QuadraticFunction func, double x) {
    return func.a * x * x + func.b * x + func.c;
}

// �־��� x�� ���� ������ȭ��(�̺�) ���
double instantaneousChange(QuadraticFunction func, double x) {
    return 2 * func.a * x + func.b;
}

// ���� [x1, x2]������ �Ѻ�ȭ�� ���
double totalChange(QuadraticFunction func, double x1, double x2) {
    return evaluateQuadratic(func, x2) - evaluateQuadratic(func, x1);
}

int main() {
    // ���� ó��
    FILE *inputFile = fopen("input_data.txt", "w");
    if (!inputFile) {
        printf("�Է� ������ ������ �� �����ϴ�.\n");
        return 1;
    }

    // �̹������� �� ������ ����Ʈ (x, y)�� ���Ͽ� ����
    fprintf(inputFile, "0 0\n");
    fprintf(inputFile, "1 1\n");
    fprintf(inputFile, "2 2\n");
    fprintf(inputFile, "3 3.2\n");
    fprintf(inputFile, "4 2.8\n");
    fprintf(inputFile, "5 2\n");
    fprintf(inputFile, "6 0.8\n");
    fclose(inputFile);

    // ���Ͽ��� ������ �б�
    FILE *readFile = fopen("input_data.txt", "r");
    if (!readFile) {
        printf("�Է� ������ ���� �� �����ϴ�.\n");
        return 1;
    }

    // ������ ����Ʈ ������ ���� �迭
    Point points[100];
    int n = 0;

    // ���Ͽ��� ������ �б�
    while (fscanf(readFile, "%lf %lf", &points[n].x, &points[n].y) == 2 && n < 100) {
        n++;
    }
    fclose(readFile);

    // �����Լ� ����
    QuadraticFunction fittedFunc = fitQuadratic(points, n);

    // ��� ���� ����
    FILE *outputFile = fopen("output_results.txt", "w");
    if (!outputFile) {
        printf("��� ������ ������ �� �����ϴ�.\n");
        return 1;
    }

    // ��� ����
    fprintf(outputFile, "�л� ���� ������ �м� ���\n");
    fprintf(outputFile, "----------------------------\n\n");
    fprintf(outputFile, "1. ������ ����\n");
    fprintf(outputFile, "���� ������ ����Ʈ ��: %d\n\n", n);

    fprintf(outputFile, "2. ȭ�� �м� (�����Լ� ����)\n");
    fprintf(outputFile, "���õ� �����Լ�: y = %.4f x^2 + %.4f x + %.4f\n\n",
            fittedFunc.a, fittedFunc.b, fittedFunc.c);

    fprintf(outputFile, "3. ������ �м�\n");
    fprintf(outputFile, "x\t���� y\t���� y\t����\n");
    double totalError = 0;
    for (int i = 0; i < n; i++) {
        double predicted = evaluateQuadratic(fittedFunc, points[i].x);
        double error = fabs(predicted - points[i].y);
        totalError += error;
        fprintf(outputFile, "%.1f\t%.1f\t%.4f\t%.4f\n",
                points[i].x, points[i].y, predicted, error);
    }
    fprintf(outputFile, "��� ����: %.4f\n\n", totalError / n);

    fprintf(outputFile, "4. �� ���� (��ȭ�� �м�)\n");
    fprintf(outputFile, "x\t������ȭ��\n");
    for (int i = 0; i <= 6; i++) {
        fprintf(outputFile, "%d\t%.4f\n", i, instantaneousChange(fittedFunc, i));
    }

    fprintf(outputFile, "\n������ �Ѻ�ȭ��\n");
    fprintf(outputFile, "����\t�Ѻ�ȭ��\n");
    for (int i = 0; i < 6; i++) {
        fprintf(outputFile, "[%d, %d]\t%.4f\n",
                i, i+1, totalChange(fittedFunc, i, i+1));
    }

    fclose(outputFile);

    // �ֿܼ��� ���
    printf("�����Լ� ���� �� �м��� �Ϸ�Ǿ����ϴ�.\n");
    printf("���õ� �����Լ�: y = %.4f x^2 + %.4f x + %.4f\n",
            fittedFunc.a, fittedFunc.b, fittedFunc.c);
    printf("����� 'output_results.txt' ���Ͽ� ����Ǿ����ϴ�.\n");

    return 0;
}