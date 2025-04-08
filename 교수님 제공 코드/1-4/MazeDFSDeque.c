// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch04/MazeDFSDeque.c

//-------------------------------------------------------------
// �ڵ� 4.9 ���� �̿��� �̷� Ž��(DFS)


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
        return; // �̷� ���� ���� ��ġ
    if (map[r][c] != '0' && map[r][c] != 'x')
        return; // �� �� �ִ� ĭ�� �ƴ�
    Element pos = { r, c };
    add_rear(pos);
}
Element pop_loc()
{
    return delete_rear();       // �Ĵ� ����(������ pop)
    // return delete_front();       // �Ĵ� ����(������ pop)
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
    init_deque();       // ��: �ʱ�ȭ
    push_loc(1, 0);     // �̷��� ���� ��ġ�� ����

    while (is_empty() == 0) {
        system("cls");
        print_maze();
        Sleep(500);     // <windows.h>

        Element here = pop_loc();
        int c = here.c;
        int r = here.r;
        if (map[r][c] == 'x') {
            printf("\n�̷� Ż�� ����\n");
            return;
        }
        else {
            map[r][c] = '.';    // �湮��
            push_loc(r - 1, c); // ��
            push_loc(r + 1, c); // ��
            push_loc(r, c - 1); // ��
            push_loc(r, c + 1); // ��
        }
    }
    printf("\n�̷� Ż�� ����\n");
}
