#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100    // 배열의 크기
struct Waiting {        // 대기 정보 구조체
    int id;             // 대기번호
    int nperson;        // 인원
    char info[32];      // 전화번호
};
typedef struct Waiting Element;
#include "CircularQueue.h"

int main(void)
{
    int num = 10; // 대기 인원 수
    Element waiting[num];

    init_queue();

    srand(time(NULL)); // 랜덤 시드 초기화
    for (int i = 1; i < num + 1; i++) {
        waiting[i].id = i;
        waiting[i].nperson = rand() % 6 + 1; // 1~6명

        generate_random_phone(waiting[i].info);

        printf("웨이팅 신청을 완료했습니다. 대기번호: %d번 인원:%d명\n",
            waiting[i].id, waiting[i].nperson);
        enqueue(waiting[i]);
    }

    while (!is_empty()) {
        Element w = dequeue();
        printf("웨이팅 번호 %d번 입장하실 차례입니다. (%d명, %s)\n",
            w.id, w.nperson, w.info);
    }


    return 0;
}
