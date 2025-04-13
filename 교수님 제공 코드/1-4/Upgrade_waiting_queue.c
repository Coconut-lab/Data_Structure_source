#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100    // �迭�� ũ��
struct Waiting {        // ��� ���� ����ü
    int id;             // ����ȣ
    int nperson;        // �ο�
    char info[32];      // ��ȭ��ȣ
};
typedef struct Waiting Element;
#include "CircularQueue.h"

int main(void)
{
    int num = 10; // ��� �ο� ��
    Element waiting[num];

    init_queue();

    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
    for (int i = 1; i < num + 1; i++) {
        waiting[i].id = i;
        waiting[i].nperson = rand() % 6 + 1; // 1~6��

        generate_random_phone(waiting[i].info);

        printf("������ ��û�� �Ϸ��߽��ϴ�. ����ȣ: %d�� �ο�:%d��\n",
            waiting[i].id, waiting[i].nperson);
        enqueue(waiting[i]);
    }

    while (!is_empty()) {
        Element w = dequeue();
        printf("������ ��ȣ %d�� �����Ͻ� �����Դϴ�. (%d��, %s)\n",
            w.id, w.nperson, w.info);
    }


    return 0;
}
