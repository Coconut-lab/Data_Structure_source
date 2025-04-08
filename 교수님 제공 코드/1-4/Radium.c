#include <stdio.h>
#include <math.h>

int main() {
    double initialAmount; // 초기 방사능량
    double halfLife;      // 반감기 (시간 단위)
    double time;          // 경과 시간 (반감기와 동일한 시간 단위)
    double remainingAmount; // 남은 방사능량

    // 사용자로부터 입력 받기
    printf("초기 방사능량을 입력하세요: ");
    scanf("%lf", &initialAmount);

    printf("반감기를 입력하세요 (시간 단위): ");
    scanf("%lf", &halfLife);

    printf("경과 시간을 입력하세요 (반감기와 동일한 시간 단위): ");
    scanf("%lf", &time);

    // 방사능 반감기 공식: N(t) = N0 * (1/2)^(t/T)
    // N(t): 시간 t에서의 방사능량
    // N0: 초기 방사능량
    // t: 경과 시간
    // T: 반감기
    remainingAmount = initialAmount * pow(0.5, time / halfLife);

    printf("\n계산 결과:\n");
    printf("초기 방사능량: %.2f\n", initialAmount);
    printf("반감기: %.2f\n", halfLife);
    printf("경과 시간: %.2f\n", time);
    printf("남은 방사능량: %.2f\n", remainingAmount);

    // 몇 번의 반감기가 지났는지 계산
    double numberOfHalfLives = time / halfLife;
    printf("경과된 반감기 수: %.2f\n", numberOfHalfLives);

    return 0;
}