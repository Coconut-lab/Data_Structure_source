#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 최대공약수(GCD) 계산 함수 - 유클리드 알고리즘 사용
int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 최소공배수(LCM) 계산 함수 - LCM = (a * b) / GCD(a, b)
int calculateLCM(int a, int b) {
    return (a * b) / calculateGCD(a, b);
}

// 소인수 분해 함수
void primeFactorization(int num, FILE *file) {
    fprintf(file, "%d의 소인수 분해: ", num);

    // 소인수분해 시작
    int factor = 2;
    int first = 1; // 첫 번째 인수인지 확인용

    while (num > 1) {
        int count = 0;

        while (num % factor == 0) {
            count++;
            num /= factor;
        }

        if (count > 0) {
            if (!first) {
                fprintf(file, " × ");
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

        // 성능 최적화: 남은 num이 소수라면 반복 중단
        if (factor * factor > num && num > 1) {
            if (!first) {
                fprintf(file, " × ");
            }
            fprintf(file, "%d", num);
            break;
        }
    }

    fprintf(file, "\n");
}

// 좌표 구조체
typedef struct {
    int x;
    int y;
} Point;

// 직선의 기울기 계산
double calculateSlope(Point p1, Point p2) {
    return (double)(p2.y - p1.y) / (p2.x - p1.x);
}

// 좌표 예측 함수 (GCD, LCM 값을 활용)
Point predictPoint(int gcd, int lcm) {
    Point result;
    result.x = lcm / gcd;  // 기울기에 기반한 x 좌표 예측
    result.y = lcm / (lcm / gcd);  // y = x / 기울기
    return result;
}

int main() {
    // 파일 생성
    FILE *outputFile = fopen("gcd_lcm_results.txt", "w");
    if (outputFile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 사용자로부터 두 숫자 입력 받기
    int num1, num2;
    printf("첫 번째 숫자를 입력하세요: ");
    scanf("%d", &num1);
    printf("두 번째 숫자를 입력하세요: ");
    scanf("%d", &num2);

    // 입력값 파일에 저장
    fprintf(outputFile, "입력 받은 숫자: %d, %d\n\n", num1, num2);

    // 소인수 분해
    fprintf(outputFile, "1. 소인수 분해\n");
    primeFactorization(num1, outputFile);
    primeFactorization(num2, outputFile);
    fprintf(outputFile, "\n");

    // GCD와 LCM 계산
    int gcd = calculateGCD(num1, num2);
    int lcm = calculateLCM(num1, num2);

    fprintf(outputFile, "2. GCD와 LCM 계산\n");
    fprintf(outputFile, "GCD(%d, %d) = %d\n", num1, num2, gcd);
    fprintf(outputFile, "LCM(%d, %d) = %d\n", num1, num2, lcm);
    fprintf(outputFile, "GCD × LCM = %d × %d = %d\n", gcd, lcm, gcd * lcm);
    fprintf(outputFile, "num1 × num2 = %d × %d = %d\n", num1, num2, num1 * num2);
    fprintf(outputFile, "\n");

    // 예시: 좌표평면 분석 (주어진 예시에 따라)
    fprintf(outputFile, "3. 좌표평면 분석\n");

    // 기본 좌표점 설정 (화이트보드 이미지 참조)
    Point p1 = {2, 1};
    Point p2 = {10, 5};
    Point p3 = {30, 15};

    // 기울기 계산
    double slope1 = calculateSlope(p1, p2);
    double slope2 = calculateSlope(p2, p3);

    fprintf(outputFile, "좌표점: (2, 1), (10, 5), (30, 15)\n");
    fprintf(outputFile, "기울기1 (점1-점2): %.2f\n", slope1);
    fprintf(outputFile, "기울기2 (점2-점3): %.2f\n", slope2);

    // GCD, LCM을 이용한 예측
    fprintf(outputFile, "\nGCD와 LCM을 활용한 예측:\n");
    fprintf(outputFile, "GCD = %d, LCM = %d\n", gcd, lcm);

    Point predicted = predictPoint(gcd, lcm);
    fprintf(outputFile, "예측 좌표: (%d, %d)\n", predicted.x, predicted.y);

    // 콘솔 출력
    printf("\n계산이 완료되었습니다.\n");
    printf("GCD(%d, %d) = %d\n", num1, num2, gcd);
    printf("LCM(%d, %d) = %d\n", num1, num2, lcm);
    printf("결과는 'gcd_lcm_results.txt' 파일에 저장되었습니다.\n");

    fclose(outputFile);
    return 0;
}