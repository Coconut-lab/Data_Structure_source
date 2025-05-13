// 두근두근 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch04/MazeDFSDeque.c

//-------------------------------------------------------------
// 코드 4.9 덱을 이용한 미로 탐색(DFS)
//-------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 프로그램은 덱(Deque)을 사용하여 미로를 깊이 우선 탐색(DFS) 방식으로 탐색하는 알고리즘을 구현합니다.
 * 미로에서 출발점부터 도착점('x')까지의 경로를 찾아 화면에 표시합니다.
 * 덱의 후단(rear) 삽입/삭제 연산을 활용하여 스택처럼 작동하게 만들어 DFS를 구현합니다.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
/*
 * [위치 구조체 정의]
 * 미로에서의 위치(행, 열)를 저장하기 위한 구조체
 */
struct Pos2D { int r; int c; };
typedef struct Pos2D Element;
#include "CircularDeque.h"

#define MAZE_DIM 6      // 미로의 크기 정의

/*
 * [미로 맵 정의]
 * '1': 벽
 * '0': 지나갈 수 있는 길
 * 'x': 도착점
 */
char map[MAZE_DIM][MAZE_DIM] = {
    { '1', '1', '1', '1', '1', '1' },
    { '0', '0', '1', '0', '0', '1' },
    { '1', '0', '0', '0', '1', '1' },
    { '1', '0', '1', '0', '1', '1' },
    { '1', '0', '1', '0', '0', 'x' },
    { '1', '1', '1', '1', '1', '1' },
};

/*
 * [위치 추가 함수]
 * 인접한 위치를 덱에 추가하는 함수
 * 매개변수: 행(r)과 열(c) 좌표
 * 
 * [동작 과정]
 * 1. 좌표가 미로 범위 내에 있는지 확인
 * 2. 해당 위치가 이동 가능한 곳인지 확인('0' 또는 'x')
 * 3. 조건을 만족하면 해당 위치를 덱의 후단에 추가
 */
void push_loc(int r, int c)
{
    if (r < 0 || c < 0 || r >= MAZE_DIM || c >= MAZE_DIM)
        return; // 미로 범위 밖의 위치
    if (map[r][c] != '0' && map[r][c] != 'x')
        return; // 갈 수 있는 칸이 아님
    Element pos = { r, c };
    add_rear(pos);      // 덱의 후단에 위치 추가
}

/*
 * [위치 제거 함수]
 * 덱에서 위치를 하나 제거하고 반환하는 함수
 * 반환값: 제거된 위치(행, 열)
 * 
 * delete_rear()를 사용하면 스택처럼 동작(LIFO)하여 DFS를 구현하고,
 * delete_front()를 사용하면 큐처럼 동작(FIFO)하여 BFS를 구현할 수 있음
 */
Element pop_loc()
{
    return delete_rear();       // 후단 삭제(스택처럼 동작 - DFS)
    // return delete_front();   // 전단 삭제(큐처럼 동작 - BFS)
}

/*
 * [미로 출력 함수]
 * 현재 미로의 상태와 탐색 위치를 화면에 출력하는 함수
 * 현재 위치는 '@'로 표시됩니다.
 */
void print_maze()
{
    Element here = get_rear();  // 현재 위치 확인
    for (int r = 0; r < MAZE_DIM; r++) {
        for (int c = 0; c < MAZE_DIM; c++)
            if (here.r == r && here.c == c) printf("@");  // 현재 위치
            else printf("%c", map[r][c]);                 // 미로 맵
        printf("\n");
    }
}

#include <windows.h>
void main()
{
    init_deque();       // 덱 초기화
    push_loc(1, 0);     // 미로의 시작 위치를 덱에 삽입

    /*
     * [메인 탐색 루프]
     * 덱이 비어있지 않는 동안 계속 탐색을 수행
     */
    while (is_empty() == 0) {
        system("cls");      // 화면 지우기
        print_maze();       // 현재 미로 상태 출력
        Sleep(500);         // 0.5초 대기 (시각적 효과)

        Element here = pop_loc();  // 현재 위치 꺼내기
        int c = here.c;
        int r = here.r;
        
        // 도착점 확인
        if (map[r][c] == 'x') {
            printf("\n미로 탈출 성공\n");
            return;
        }
        else {
            map[r][c] = '.';    // 방문 표시
            
            /*
             * [인접 위치 탐색]
             * 상하좌우 네 방향의 인접 위치를 덱에 추가
             */
            push_loc(r - 1, c); // 상
            push_loc(r + 1, c); // 하
            push_loc(r, c - 1); // 좌
            push_loc(r, c + 1); // 우
        }
    }
    printf("\n미로 탈출 실패\n");  // 모든 가능한 경로를 탐색했지만 출구를 찾지 못함
}
