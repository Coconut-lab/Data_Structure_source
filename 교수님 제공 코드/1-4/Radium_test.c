// 방사선 감쇠 시뮬레이션 프로그램
// N(t) = N0 * e^(-kt)를 이용하여 t년 후의 남은 방사선 양을 계산

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// CircularQueue.h에서 필요한 매크로와 타입 정의
#define MAX_SIZE 100
typedef double Element;

// CircularQueue.h 포함
#include "CircularQueue.h"

// 방사선 감쇠 함수: N(t) = N0 * e^(-kt)
double calculate_radiation(double N0, double k, double t) {
    return N0 * pow(M_E, -k * t);
}

int main() {
    // 3개의 큐 초기화 (N0, k, t를 저장하기 위한 큐)
    Element N0_queue[MAX_SIZE];
    Element k_queue[MAX_SIZE];
    Element t_queue[MAX_SIZE];

    // 큐 초기화 (전역 변수를 사용하므로 큐마다 데이터 배열을 따로 설정)
    Element* data_backup = data;

    // N0 큐 초기화
    data = N0_queue;
    init_queue();

    // k 큐 초기화
    data = k_queue;
    init_queue();

    // t 큐 초기화
    data = t_queue;
    init_queue();

    FILE *input_file, *output_file;

    // 입력 파일 열기
    input_file = fopen("radiation_input.txt", "r");
    if (input_file == NULL) {
        printf("입력 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 출력 파일 열기
    output_file = fopen("radiation_output.txt", "w");
    if (output_file == NULL) {
        printf("출력 파일을 생성할 수 없습니다.\n");
        fclose(input_file);
        return 1;
    }

    // 파일에서 데이터 읽기
    double n0, k, t;
    while (fscanf(input_file, "%lf %lf %lf", &n0, &k, &t) == 3) {
        // N0 큐에 초기 방사선 양 입력
        data = N0_queue;
        enqueue(n0);

        // k 큐에 감쇠 계수 입력
        data = k_queue;
        enqueue(k);

        // t 큐에 시간 입력
        data = t_queue;
        enqueue(t);
    }

    // 파일에서 읽은 데이터로 방사선 감쇠 계산
    fprintf(output_file, "초기방사선양(N0)\t감쇠계수(k)\t시간(t)\t\t남은 방사선양(N(t))\n");
    fprintf(output_file, "--------------------------------------------------------------------\n");

    while (1) {
        // 모든 큐가 비어있으면 종료
        data = N0_queue;
        if (is_empty()) break;

        // 큐에서 값 추출
        data = N0_queue;
        double current_n0 = dequeue();

        data = k_queue;
        double current_k = dequeue();

        data = t_queue;
        double current_t = dequeue();

        // 방사선 감쇠 계산
        double result = calculate_radiation(current_n0, current_k, current_t);

        // 결과를 파일에 기록
        fprintf(output_file, "%.4lf\t\t%.4lf\t\t%.4lf\t\t%.4lf\n",
                current_n0, current_k, current_t, result);
    }

    // 원래 데이터 배열 복원
    data = data_backup;

    // 파일 닫기
    fclose(input_file);
    fclose(output_file);

    printf("방사선 감쇠 시뮬레이션이 완료되었습니다.\n");
    printf("결과가 'radiation_output.txt' 파일에 저장되었습니다.\n");

    return 0;
}