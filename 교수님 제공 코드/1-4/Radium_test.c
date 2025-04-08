#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 8

// Element 타입 정의 - 방사선 붕괴 시뮬레이션을 위한 구조체
typedef struct {
    double initialAmount;    // 초기 방사성 물질의 양(g)
    double decayConstant;    // 붕괴 상수(lambda)
    double time;             // 경과 시간(년)
} Element;

#include "CircularQueue.h"

// 큐 내용을 화면에 출력하는 함수
void print_queue(char msg[]) {
    printf("%s front=%d, rear=%d --> \n", msg, front, rear);
    int size = (rear - front + MAX_SIZE) % MAX_SIZE;

    for (int i = front + 1; i <= front + size; i++) {
        int idx = i % MAX_SIZE;
        printf("시뮬레이션 %d: 초기량=%.6fg, 붕괴상수=%.8f/년, 시간=%.2f년\n",
               i - front, data[idx].initialAmount, data[idx].decayConstant, data[idx].time);
    }
    printf("\n");
}

// 방사선 붕괴 계산 및 결과 출력 함수
void calculate_decay(Element elem) {
    double remainingAmount = elem.initialAmount * exp(-elem.decayConstant * elem.time);
    double activityInitial = elem.initialAmount * elem.decayConstant;
    double activityFinal = remainingAmount * elem.decayConstant;
    double halfLife = log(2) / elem.decayConstant;

    printf("\n===== 방사능 붕괴 계산 결과 =====\n");
    printf("초기 방사성 물질의 양: %.6f g\n", elem.initialAmount);
    printf("반감기: %.2f 년\n", halfLife);
    printf("붕괴 상수(λ): %.8f /년\n", elem.decayConstant);
    printf("경과 시간: %.2f 년\n", elem.time);
    printf("남은 방사성 물질의 양: %.6f g\n", remainingAmount);
    printf("감소 비율: %.2f%%\n", (1 - remainingAmount/elem.initialAmount) * 100);
    printf("초기 방사능 활성도(추정): %.6e Bq\n", activityInitial);
    printf("최종 방사능 활성도(추정): %.6e Bq\n", activityFinal);
    printf("==============================\n\n");
}

// 시뮬레이션 데이터 입력 함수
Element input_simulation_data() {
    Element elem;

    printf("초기 방사성 물질의 양(g)을 입력하세요: ");
    scanf("%lf", &elem.initialAmount);

    printf("반감기(년)를 입력하세요: ");
    double halfLife;
    scanf("%lf", &halfLife);
    elem.decayConstant = log(2) / halfLife;

    printf("경과 시간(년)을 입력하세요: ");
    scanf("%lf", &elem.time);

    return elem;
}

int main() {
    init_queue();
    int choice;

    while (1) {
        printf("\n====== 방사선 붕괴 시뮬레이션 ======\n");
        printf("1. 새로운 시뮬레이션 추가\n");
        printf("2. 시뮬레이션 계산 및 제거\n");
        printf("3. 현재 시뮬레이션 목록 보기\n");
        printf("4. 다음 시뮬레이션 보기 (peek)\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("프로그램을 종료합니다.\n");
                exit(0);

            case 1:
                if (is_full()) {
                    printf("큐가 가득 찼습니다. 먼저 기존 시뮬레이션을 계산해주세요.\n");
                } else {
                    Element elem = input_simulation_data();
                    enqueue(elem);
                    printf("시뮬레이션이 큐에 추가되었습니다.\n");
                }
                break;

            case 2:
                if (is_empty()) {
                    printf("큐가 비어있습니다. 먼저 시뮬레이션을 추가해주세요.\n");
                } else {
                    Element elem = dequeue();
                    printf("큐에서 시뮬레이션을 가져와 계산합니다.\n");
                    calculate_decay(elem);
                }
                break;

            case 3:
                if (is_empty()) {
                    printf("큐가 비어있습니다.\n");
                } else {
                    print_queue("현재 큐 상태:");
                }
                break;

            case 4:
                if (is_empty()) {
                    printf("큐가 비어있습니다.\n");
                } else {
                    Element elem = peek();
                    printf("다음 처리될 시뮬레이션: 초기량=%.6fg, 붕괴상수=%.8f/년, 시간=%.2f년\n",
                           elem.initialAmount, elem.decayConstant, elem.time);
                }
                break;

            default:
                printf("잘못된 선택입니다. 다시 시도해주세요.\n");
        }
    }

    return 0;
}