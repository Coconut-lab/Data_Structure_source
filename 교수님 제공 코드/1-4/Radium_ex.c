#include <stdio.h>
#include <math.h>

int main() {
    double initialAmount;    // 초기 방사성 물질의 양(g)
    double halfLife;         // 반감기(년)
    double time;             // 경과 시간(년)
    double decayConstant;    // 붕괴 상수(lambda)
    double remainingAmount;  // 남은 방사성 물질의 양(g)

    printf("초기 방사성 물질의 양(g)을 입력하세요: ");
    scanf("%lf", &initialAmount);

    printf("반감기(년)를 입력하세요: ");
    scanf("%lf", &halfLife);

    printf("경과 시간(년)을 입력하세요: ");
    scanf("%lf", &time);

    decayConstant = log(2) / halfLife;

    remainingAmount = initialAmount * exp(-decayConstant * time);

    printf("\n===== 방사능 붕괴 계산 결과 =====\n");
    printf("초기 방사성 물질의 양: %.6f g\n", initialAmount);
    printf("반감기: %.2f 년\n", halfLife);
    printf("붕괴 상수(λ): %.8f /년\n", decayConstant);
    printf("경과 시간: %.2f 년\n", time);
    printf("남은 방사성 물질의 양: %.6f g\n", remainingAmount);
    printf("\n");

    return 0;
}