// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch04/waiting_queue.c


//-------------------------------------------------------------
// �ڵ� 4.3 ť�� ������ ���� �����ϱ�


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100    // �迭�� ũ��
struct Waiting {        // ��� ���� ����ü
    int id;             // ����ȣ
    int nperson;        // �ο�
    char info[32];      // ��ȭ��ȣ
};
typedef struct Waiting Element;
#include "CircularQueue.h"

void main()
{
    Element waiting[4] = {
        { 12, 2, "010-xxxx-1234" },
        { 13, 4, "010-xxxx-7809" },
        { 14, 3, "010-xxxx-4785" },
        { 15, 2, "010-xxxx-7345" } };

    init_queue();
    for (int i = 0; i < 4; i++) {
        printf("������ ��û�� �Ϸ��߽��ϴ�. ����ȣ: %d�� �ο�:%d��\n",
            waiting[i].id, waiting[i].nperson);
        enqueue(waiting[i]);
    }
    while (!is_empty()) {
        Element w = dequeue();
        printf("������ ��ȣ %d�� �����Ͻ� �����Դϴ�. (%d��, %s)\n",
            w.id, w.nperson, w.info);
    }
}
