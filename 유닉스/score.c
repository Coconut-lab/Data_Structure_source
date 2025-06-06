#include "score.h"

// 총점을 계산하는 함수
double totalScore(double korean, double english, double math) {
    return korean + english + math;
}

// 평균 계산 함수
double avgScore(double korean, double english, double math) {
    return totalScore(korean, english, math) / 3.0;
}

// 학점을 결정하는 함수
char getGrade(double average) {
    if (average >= 90.0) {
        return 'A';
    } else if (average >= 80.0) {
        return 'B';
    } else if (average >= 70.0) {
        return 'C';
    } else if (average >= 60.0) {
        return 'D';
    } else {
        return 'F';
    }
}
