// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch04/CircularDeque.h


//-------------------------------------------------------------
// �ڵ� 4.7 �迭�� �̿��� ���� ���� ����


#include "CircularQueue.h"

// ���� ������: CircularQueue�� �̹� ���ǵǾ� ����
// ���� �ֿ� ����� -----------------------------------
// ť���� �̹� ������ ����� Ȱ���ϴ� �����

void init_deque() // ���� �ʱ�ȭ�� ť�� �ʱ�ȭ �Լ��� ȣ���ϸ� ��
{
    init_queue();
}
void add_rear(Element val) // �Ĵ� ������ ť�� enqueue()�� ����
{
    enqueue(val);
}
Element delete_front() // ���� ������ ť�� dequeue()�� ����
{
    return dequeue();
}
Element get_front() // ���� ������ ť�� peek()�� ����
{
    return peek();
}
// ť�� ���� ���ο� �����
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

