// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch04/CircularDeque.h

//-------------------------------------------------------------
// 코드 4.7 배열을 이용한 원형 덱의 구현
//-------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 헤더 파일은 배열을 이용한 원형 덱(Deque: Double-Ended Queue)의 구현을 제공합니다.
 * 덱은 양쪽 끝에서 삽입과 삭제가 모두 가능한 자료구조입니다.
 * 이 구현은 CircularQueue를 확장하여 덱의 기능을 구현합니다.
 */

#include "CircularQueue.h"

/*
 * [구현 전략]
 * CircularQueue가 이미 정의되어 있음
 * 덱의 주요 연산은 기존 큐 연산을 활용하거나, 추가 구현합니다.
 * 1. 큐의 rear 방향 연산: 기존 큐 함수 활용
 * 2. 큐의 front 방향 연산: 새롭게 구현
 */

/*
 * [덱 초기화 함수]
 * 덱을 초기화하는 함수 - 기존 큐 초기화 함수를 호출
 */
void init_deque()
{
    init_queue();
}

/*
 * [덱 후단 삽입 함수]
 * 덱의 후단(rear)에 데이터를 삽입하는 함수
 * 큐의 enqueue() 함수와 동일한 동작
 */
void add_rear(Element val)
{
    enqueue(val);
}

/*
 * [덱 전단 삭제 함수]
 * 덱의 전단(front)에서 데이터를 삭제하고 반환하는 함수
 * 큐의 dequeue() 함수와 동일한 동작
 */
Element delete_front()
{
    return dequeue();
}

/*
 * [덱 전단 조회 함수]
 * 덱의 전단(front)의 데이터를 삭제하지 않고 반환하는 함수
 * 큐의 peek() 함수와 동일한 동작
 */
Element get_front()
{
    return peek();
}

/*
 * [덱 전단 삽입 함수]
 * 덱의 전단(front)에 데이터를 삽입하는 함수
 * 이는 큐에는 없는 덱만의 고유 기능
 * 
 * [동작 과정]
 * 1. 덱이 가득 찼는지 확인
 * 2. front 위치에 데이터 저장
 * 3. front를 왼쪽(앞쪽)으로 이동 - 원형 구조를 위해 모듈로 연산 사용
 */
void add_front(Element val)
{
    if (is_full())
        error("Overflow Error!");
    data[front] = val;
    front = (front - 1 + MAX_SIZE) % MAX_SIZE;
}

/*
 * [덱 후단 삭제 함수]
 * 덱의 후단(rear)에서 데이터를 삭제하고 반환하는 함수
 * 이는 큐에는 없는 덱만의 고유 기능
 * 
 * [동작 과정]
 * 1. 덱이 비어있는지 확인
 * 2. 현재 rear 위치 저장
 * 3. rear를 왼쪽(앞쪽)으로 이동 - 원형 구조를 위해 모듈로 연산 사용
 * 4. 이전 rear 위치의 데이터 반환
 */
Element delete_rear()
{
    if (is_empty())
        error("Underflow Error!");
    int prev = rear;
    rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;
    return data[prev];
}

/*
 * [덱 후단 조회 함수]
 * 덱의 후단(rear)의 데이터를 삭제하지 않고 반환하는 함수
 * 이는 큐에는 없는 덱만의 고유 기능
 */
Element get_rear()
{
    if (is_empty())
        error("Underflow Error!");
    return data[rear];
}
