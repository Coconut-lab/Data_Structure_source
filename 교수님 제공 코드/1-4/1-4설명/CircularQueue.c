// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch04/CircularQueue.c

//-------------------------------------------------------------
// 코드 4.2 원형 큐의 활용
//-------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 프로그램은 배열 기반 원형 큐의 기본 사용법을 보여주는 예제입니다.
 * 원형 큐에 데이터를 삽입(enqueue)하고 삭제(dequeue)하는 과정을 통해
 * 원형 큐의 동작 방식을 시각적으로 확인할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 8        // 큐의 최대 크기를 8로 정의

typedef int Element;      // 큐에 저장할 데이터 타입을 int로 정의
#include "CircularQueue.h" // 원형 큐 헤더 파일 포함

/*
 * [큐 출력 함수]
 * 현재 큐의 상태와 저장된 모든 데이터를 출력하는 함수
 * 매개변수: 출력 시 표시할 메시지
 * 
 * [동작 과정]
 * 1. 큐의 front와 rear 값을 출력
 * 2. 큐의 크기를 계산 - 원형 큐에서는 (rear-front+MAX_SIZE)%MAX_SIZE로 계산
 * 3. front+1부터 모든 데이터 요소를 출력
 */
void print_queue(char msg[]) {
    printf("%s front=%d, rear=%d --> ", msg, front, rear);
    int size = (rear - front + MAX_SIZE) % MAX_SIZE;
    for (int i = front + 1; i <= front + size; i++)
        printf("%2d ", data[i % MAX_SIZE]);
    printf("\n");
}

void main()
{
    // 큐 초기화 (front = rear = 0으로 설정)
    init_queue();
    
    // 1부터 6까지의 숫자를 큐에 삽입
    for (int i = 1; i < 7; i++) enqueue(i);
    print_queue("enqueue 1~6: ");
    
    /*
     * [상태 분석]
     * 위 코드 실행 후 큐의 상태:
     * front=0, rear=6
     * 데이터: 1 2 3 4 5 6
     */

    // 큐에서 4개의 데이터를 삭제
    for (int i = 0; i < 4; i++) dequeue();
    print_queue("dequeue 4회: ");
    
    /*
     * [상태 분석]
     * 위 코드 실행 후 큐의 상태:
     * front=4, rear=6
     * 데이터: 5 6
     * front가 4로 이동했지만, 원형 큐이므로 앞쪽 배열 공간을 재사용할 수 있음
     */

    // 7부터 9까지의 숫자를 큐에 추가 삽입
    for (int i = 7; i < 10; i++) enqueue(i);
    print_queue("enqueue 7~9: ");
    
    /*
     * [상태 분석]
     * 위 코드 실행 후 큐의 상태:
     * front=4, rear=1 (원형으로 rear가 배열의 앞쪽으로 이동)
     * 데이터: 5 6 7 8 9
     * 
     * 이는 원형 큐의 장점을 잘 보여줍니다:
     * 1. 배열의 앞부분이 비어있을 때 그 공간을 활용할 수 있음
     * 2. 모듈로 연산을 통해 배열의 끝과 시작이 연결된 것처럼 동작
     */
}
