#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// 데이터 포인트 구조체
typedef struct {
    double x;
    double y;
} Point;

// 이차함수 계수를 저장하는 구조체
typedef struct {
    double a;  // x^2 계수
    double b;  // x 계수
    double c;  // 상수항
} QuadraticFunction;

// 이차함수 피팅 함수 (최소제곱법)
QuadraticFunction fitQuadratic(Point* points, int n) {
    // 선형 방정식 시스템 구성을 위한 합계 변수
    double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0, sum_xy = 0, sum_x2y = 0;

    // 합계 계산
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

    // 연립방정식 해결 (행렬식 사용)
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

// 주어진 x에 대한 이차함수 값 계산
double evaluateQuadratic(QuadraticFunction func, double x) {
    return func.a * x * x + func.b * x + func.c;
}

// 주어진 x에 대한 순간변화율(미분) 계산
double instantaneousChange(QuadraticFunction func, double x) {
    return 2 * func.a * x + func.b;
}

// 구간 [x1, x2]에서의 총변화량 계산
double totalChange(QuadraticFunction func, double x1, double x2) {
    return evaluateQuadratic(func, x2) - evaluateQuadratic(func, x1);
}

int main() {
    // 파일 처리
    FILE *inputFile = fopen("input_data.txt", "w");
    if (!inputFile) {
        printf("입력 파일을 생성할 수 없습니다.\n");
        return 1;
    }

    // 이미지에서 본 데이터 포인트 (x, y)를 파일에 저장
    fprintf(inputFile, "0 0\n");
    fprintf(inputFile, "1 1\n");
    fprintf(inputFile, "2 2\n");
    fprintf(inputFile, "3 3.2\n");
    fprintf(inputFile, "4 2.8\n");
    fprintf(inputFile, "5 2\n");
    fprintf(inputFile, "6 0.8\n");
    fclose(inputFile);

    // 파일에서 데이터 읽기
    FILE *readFile = fopen("input_data.txt", "r");
    if (!readFile) {
        printf("입력 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    // 데이터 포인트 저장을 위한 배열
    Point points[100];
    int n = 0;

    // 파일에서 데이터 읽기
    while (fscanf(readFile, "%lf %lf", &points[n].x, &points[n].y) == 2 && n < 100) {
        n++;
    }
    fclose(readFile);

    // 이차함수 피팅
    QuadraticFunction fittedFunc = fitQuadratic(points, n);

    // 결과 파일 생성
    FILE *outputFile = fopen("output_results.txt", "w");
    if (!outputFile) {
        printf("출력 파일을 생성할 수 없습니다.\n");
        return 1;
    }

    // 결과 저장
    fprintf(outputFile, "학생 족구 데이터 분석 결과\n");
    fprintf(outputFile, "----------------------------\n\n");
    fprintf(outputFile, "1. 데이터 생성\n");
    fprintf(outputFile, "읽은 데이터 포인트 수: %d\n\n", n);

    fprintf(outputFile, "2. 화귀 분석 (이차함수 피팅)\n");
    fprintf(outputFile, "피팅된 이차함수: y = %.4f x^2 + %.4f x + %.4f\n\n",
            fittedFunc.a, fittedFunc.b, fittedFunc.c);

    fprintf(outputFile, "3. 데이터 분석\n");
    fprintf(outputFile, "x\t원본 y\t예측 y\t오차\n");
    double totalError = 0;
    for (int i = 0; i < n; i++) {
        double predicted = evaluateQuadratic(fittedFunc, points[i].x);
        double error = fabs(predicted - points[i].y);
        totalError += error;
        fprintf(outputFile, "%.1f\t%.1f\t%.4f\t%.4f\n",
                points[i].x, points[i].y, predicted, error);
    }
    fprintf(outputFile, "평균 오차: %.4f\n\n", totalError / n);

    fprintf(outputFile, "4. 비선 적합 (변화량 분석)\n");
    fprintf(outputFile, "x\t순간변화량\n");
    for (int i = 0; i <= 6; i++) {
        fprintf(outputFile, "%d\t%.4f\n", i, instantaneousChange(fittedFunc, i));
    }

    fprintf(outputFile, "\n구간별 총변화량\n");
    fprintf(outputFile, "구간\t총변화량\n");
    for (int i = 0; i < 6; i++) {
        fprintf(outputFile, "[%d, %d]\t%.4f\n",
                i, i+1, totalChange(fittedFunc, i, i+1));
    }

    fclose(outputFile);

    // 콘솔에도 출력
    printf("이차함수 피팅 및 분석이 완료되었습니다.\n");
    printf("피팅된 이차함수: y = %.4f x^2 + %.4f x + %.4f\n",
            fittedFunc.a, fittedFunc.b, fittedFunc.c);
    printf("결과는 'output_results.txt' 파일에 저장되었습니다.\n");

    return 0;
}