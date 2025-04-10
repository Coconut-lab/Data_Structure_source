// 방사선 감쇠 시뮬레이션 프로그램
// N(t) = N0 * e^(-kt)를 이용하여 t년 후의 남은 방사선 양을 계산

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// CircularQueue.h에서 필요한 매크로와 타입 정의
#define MAX_SIZE 100
typedef double Element;

// 큐 구조체 정의
typedef struct {
    Element data[MAX_SIZE]; // 요소의 배열
    int front;              // 전단 인덱스
    int rear;               // 후단 인덱스
} CircularQueue;

// 큐 관련 함수 정의
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

void init_queue(CircularQueue* q) {
    q->front = q->rear = 0;
}

int is_empty(CircularQueue* q) {
    return q->front == q->rear;
}

int is_full(CircularQueue* q) {
    return q->front == (q->rear + 1) % MAX_SIZE;
}

void enqueue(CircularQueue* q, Element val) {
    if (is_full(q))
        error("Overflow Error!");
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = val;
}

Element dequeue(CircularQueue* q) {
    if (is_empty(q))
        error("Underflow Error!");
    q->front = (q->front + 1) % MAX_SIZE;
    return q->data[q->front];
}

Element peek(CircularQueue* q) {
    if (is_empty(q))
        error("Underflow Error!");
    return q->data[(q->front + 1) % MAX_SIZE];
}

// 방사선 감쇠 함수: N(t) = N0 * e^(-kt)
double calculate_radiation(double N0, double k, double t) {
    return N0 * exp(-k * t);  // pow(M_E, -k * t) 대신 exp 함수 사용
}

int main() {
    // 3개의 큐 초기화 (N0, k, t를 저장하기 위한 큐)
    CircularQueue N0_queue, k_queue, t_queue;

    // 큐 초기화
    init_queue(&N0_queue);
    init_queue(&k_queue);
    init_queue(&t_queue);

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
        // 각 큐에 데이터 입력
        enqueue(&N0_queue, n0);
        enqueue(&k_queue, k);
        enqueue(&t_queue, t);
    }

    // 파일에서 읽은 데이터로 방사선 감쇠 계산
    fprintf(output_file, "초기방사선양(N0)\t감쇠계수(k)\t시간(t)\t\t남은 방사선양(N(t))\n");
    fprintf(output_file, "--------------------------------------------------------------------\n");

    while (!is_empty(&N0_queue)) {
        // 큐에서 값 추출
        double current_n0 = dequeue(&N0_queue);
        double current_k = dequeue(&k_queue);
        double current_t = dequeue(&t_queue);

        // 방사선 감쇠 계산
        double result = calculate_radiation(current_n0, current_k, current_t);

        // 결과를 파일에 기록
        fprintf(output_file, "%.4lf\t\t%.4lf\t\t%.4lf\t\t%.4lf\n",
                current_n0, current_k, current_t, result);
    }

    // 파일 닫기
    fclose(input_file);
    fclose(output_file);

    printf("방사선 감쇠 시뮬레이션이 완료되었습니다.\n");
    printf("결과가 'radiation_output.txt' 파일에 저장되었습니다.\n");

    return 0;
}