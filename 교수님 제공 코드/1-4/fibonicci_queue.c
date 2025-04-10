// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch04/fibonacci_queue.c


// �ڵ� 4.4 ť�� �̿��� �Ǻ���ġ �� ���ϱ�

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5      // �迭�� ũ��
typedef int Element;    // Element�� �ڷ��� ����
#include "CircularQueue.h"

int fibonacci(int n)
{
    if (n <= 1) return n;

    init_queue();
    enqueue(0);
    enqueue(1);
    for (int i = 2; i <= n; i++) {
        int n1 = dequeue();
        int n2 = peek();
        enqueue(n1 + n2); // F(n) = F(n-2) + F(n-1)
    }
    dequeue(); // ť���� F(n-1), F(n)�� ���� ����
    return dequeue(); // F(n)�� ��ȯ
}

int main(void)
{
    printf("�Ǻ���ġ ����: ");
    for (int i = 0; i < 16; i++)
        printf("%d,", fibonacci(i));
    printf("\n\n");

    return 0;
}
