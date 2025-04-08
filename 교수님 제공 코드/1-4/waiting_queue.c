// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch04/waiting_queue.c


//-------------------------------------------------------------
// 코드 4.3 큐에 웨이팅 정보 저장하기


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100    // 배열의 크기
struct Waiting {        // 대기 정보 구조체
    int id;             // 대기번호
    int nperson;        // 인원
    char info[32];      // 전화번호
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
        printf("웨이팅 신청을 완료했습니다. 대기번호: %d번 인원:%d명\n",
            waiting[i].id, waiting[i].nperson);
        enqueue(waiting[i]);
    }
    while (!is_empty()) {
        Element w = dequeue();
        printf("웨이팅 번호 %d번 입장하실 차례입니다. (%d명, %s)\n",
            w.id, w.nperson, w.info);
    }
}
