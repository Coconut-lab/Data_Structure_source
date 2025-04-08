// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch04/CircularDeque.h


//-------------------------------------------------------------
// 코드 4.7 배열을 이용한 원형 덱의 구현


#include "CircularQueue.h"

// 덱의 데이터: CircularQueue에 이미 정의되어 있음
// 덱의 주요 연산들 -----------------------------------
// 큐에서 이미 구현된 기능을 활용하는 연산들

void init_deque() // 덱의 초기화는 큐의 초기화 함수를 호출하면 됨
{
    init_queue();
}
void add_rear(Element val) // 후단 삽입은 큐의 enqueue()와 동일
{
    enqueue(val);
}
Element delete_front() // 전단 삭제는 큐의 dequeue()와 동일
{
    return dequeue();
}
Element get_front() // 전단 참조는 큐의 peek()와 동일
{
    return peek();
}
// 큐에 없는 새로운 연산들
void add_front(Element val)
{
    if (is_full())
        error("Overflow Error!");
    data[front] = val;
    front = (front - 1 + MAX_SIZE) % MAX_SIZE;
}
Element delete_rear()
{
    if (is_empty())
        error("Underflow Error!");
    int prev = rear;
    rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;
    return data[prev];
}
Element get_rear()
{
    if (is_empty())
        error("Underflow Error!");
    return data[rear];
}

