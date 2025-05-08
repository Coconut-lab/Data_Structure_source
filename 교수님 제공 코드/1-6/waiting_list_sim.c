// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch06/waiting_list_sim.c


//--------------------------------------------------------------------
// 코드 6.9: 웨이팅 리스트 프로그램

#include <stdio.h>
#include <stdlib.h>
struct Waiting {    // 맛집 웨이팅 큐를 위한 구조체
    int id;         // 대기번호
    int nperson;    // 인원
    char info[32];  // 전화번호
};
typedef struct Waiting Element; // Element의 자료형 정의
#include "DblLinkedList.h"      // 이중 연결 리스트 사용

// (1) 새로운 웨이팅 등록을 위한 reserve(nperson, info) 연산
void reserve(int nperson, const char info[])
{
    static int id = 0;
    Element e;
    e.id = ++id;                // 대기 번호 자동 부여
    e.nperson = nperson;
    strcpy_s(e.info, 32, info);
    insert(size(), e);          // 리스트의 맨 뒤에 추가
    printf("<등록> 번호 %d: 인원 %d명 %s\n", e.id, e.nperson, e.info);
}
// (2) 웨이팅 순서 확인을 위한 find(wid) 연산
void find(int wid)
{
    int nTeam = 0, nPeople = 0; // 앞의 팀 수와 인원 계산을 위한 변수
    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            printf("<확인> 번호 %d번 앞 대기팀: %d팀 %d명\n", wid, nTeam, nPeople);
            return;
        }
        nTeam += 1;             // 앞의 팀
        nPeople += e.nperson;   // 앞의 대기 인원
    }
}
// (3) 웨이팅 취소를 위한 calcel(wid) 연산
void cancel(int wid)
{
    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            delete(pos);
            printf("<취소> %d번 웨이팅이 취소되었습니다.\n", wid);
            return;
        }
    }
}
// (4) 웨이팅 순서 한 칸 뒤로 밀기를 위한 delay(id) 연산
void delay(int wid)
{
    for (int pos = 0; pos < size() - 1; pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            delete(pos);
            insert(pos + 1, e);
            printf("<연기> %d번 웨이팅이 한 칸 연기되었습니다.\n", wid);
            return;
        }
    }
}
// (5) 전체 웨이팅 리스트 출력
void print()
{
    printf("<출력>\n");
    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);
        printf(" 번호 %2d: %d명 %s\n", e.id, e.nperson, e.info);
    }
    printf("\n");
}
// (6) 손님 입장시키기
void service()
{
    Element e = delete(0);
    printf("<입장> %d번 손님 입장 (%d명, %s)\n", e.id, e.nperson, e.info);
}
void main()
{
    init_list();
    print();
    reserve(2, "010-xxxx-8762");
    reserve(2, "010-xxxx-3303");
    reserve(5, "010-xxxx-1212");
    reserve(1, "010-xxxx-2305");
    print();

    service();
    print();

    reserve(3, "010-xxxx-4949");
    reserve(4, "010-xxxx-7345");
    print();

    find(4);
    delay(3);
    delay(3);
    print();
    cancel(5);
    print();

    destroy_list();
}


#ifdef XXX
// 내 대기 수정하기: replace() 연산 추가해야 함
void modify()
{
    int	wid;
    printf("수정하실 웨이팅 번호를 입력하세요: ");
    scanf_s("%d", &wid);

    for (int pos = 0; pos < size() - 1; pos++) {
        Element e = get_entry(pos);
        if (e.id == wid) {
            printf("대기번호 %2d: %d명 %s\n", e.id, e.nperson, e.info);
            printf("인원과 전화번호를 다시 입력하세요: ");
            scanf_s("%d%s", &e.nperson, e.info, 32);
            replace(pos, e);
            printf("%d번 웨이팅이 수정되었습니다.\n", wid);
            return;
        }
    }
}
#endif
