#include "score.h"

int main(void) {
    double korean, english, math;
    double total, average;
    char grade;
    
    // 점수 입력받기
    printf("국어 영어 수학 점수를 입력하세요: ");
    scanf("%lf %lf %lf", &korean, &english, &math);
    
    // 총점과 평균 계산
    total = totalScore(korean, english, math);
    average = avgScore(korean, english, math);
    grade = getGrade(average);
    
    // 결과 출력 (소수점 두 번째 자리까지)
    printf("\n=== 성적 결과 ===\n");
    printf("국어: %.2f\n", korean);
    printf("영어: %.2f\n", english);
    printf("수학: %.2f\n", math);
    printf("총점: %.2f\n", total);
    printf("평균: %.2f\n", average);
    printf("학점: %c\n", grade);
    
    return 0;
}
