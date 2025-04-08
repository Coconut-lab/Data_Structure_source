// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch04/MazeDFSDeque.c

//-------------------------------------------------------------
// 코드 4.9 덱를 이용한 미로 탐색(DFS)


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
struct Pos2D { int r; int c; };
typedef struct Pos2D Element;
#include "CircularDeque.h"

#define MAZE_DIM 6
char map[MAZE_DIM][MAZE_DIM] = {
    { '1', '1', '1', '1', '1', '1' },
    { '0', '0', '1', '0', '0', '1' },
    { '1', '0', '0', '0', '1', '1' },
    { '1', '0', '1', '0', '1', '1' },
    { '1', '0', '1', '0', '0', 'x' },
    { '1', '1', '1', '1', '1', '1' },
};

void push_loc(int r, int c)
{
    if (r < 0 || c < 0 || r >= MAZE_DIM || c >= MAZE_DIM)
        return; // 미로 범위 밖의 위치
    if (map[r][c] != '0' && map[r][c] != 'x')
        return; // 갈 수 있는 칸이 아님
    Element pos = { r, c };
    add_rear(pos);
}
Element pop_loc()
{
    return delete_rear();       // 후단 삭제(스택의 pop)
    // return delete_front();       // 후단 삭제(스택의 pop)
}

void print_maze()
{
    Element here = get_rear();
    for (int r = 0; r < MAZE_DIM; r++) {
        for (int c = 0; c < MAZE_DIM; c++)
            if (here.r == r && here.c == c) printf("@");
            else printf("%c", map[r][c]);
        printf("\n");
    }
}

#include <windows.h>
void main()
{
    init_deque();       // 덱: 초기화
    push_loc(1, 0);     // 미로의 시작 위치를 저장

    while (is_empty() == 0) {
        system("cls");
        print_maze();
        Sleep(500);     // <windows.h>

        Element here = pop_loc();
        int c = here.c;
        int r = here.r;
        if (map[r][c] == 'x') {
            printf("\n미로 탈출 성공\n");
            return;
        }
        else {
            map[r][c] = '.';    // 방문함
            push_loc(r - 1, c); // 상
            push_loc(r + 1, c); // 하
            push_loc(r, c - 1); // 좌
            push_loc(r, c + 1); // 우
        }
    }
    printf("\n미로 탈출 실패\n");
}
