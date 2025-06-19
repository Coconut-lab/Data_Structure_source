// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch08/GraphSrchAM.c


//--------------------------------------------------------------------
// 코드 8.3 그래프 탐색(인접 행렬 표현)


#include <stdio.h>
#include <stdlib.h>
#define MAX_VSIZE 100   // 최대 정점 수
typedef char VElement;  // 정점의 자료형 정의

int vsize = 8;          // 그래프의 정점 수
VElement vdata[MAX_VSIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
int adj[MAX_VSIZE][MAX_VSIZE] = {
    { 0, 1, 1, 0, 0, 0, 0, 0 }, // A
    { 1, 0, 0, 1, 0, 0, 0, 0 }, // B
    { 1, 0, 0, 1, 1, 0, 0, 0 }, // C
    { 0, 1, 1, 0, 0, 1, 0, 0 }, // D
    { 0, 0, 1, 0, 0, 0, 1, 1 }, // E
    { 0, 0, 0, 1, 0, 0, 0, 0 }, // F
    { 0, 0, 0, 0, 1, 0, 0, 1 }, // G
    { 0, 0, 0, 0, 1, 0, 1, 0 } // H
};

#define PrintVtx(i) (printf("%c ", vdata[i]))

int visited[MAX_VSIZE]; // 방문 표시 리스트
void reset_visited()
{
    for (int i = 0; i < vsize; i++)
        visited[i] = 0;
}
void DFS(int v)
{
    visited[v] = 1;
    PrintVtx(v); // 정점 v 방문
    for (int w = 0; w < vsize; w++)
        if (adj[v][w] != 0 && visited[w] == 0)
            DFS(w);
}

#define MAX_SIZE 100            // 큐 요소를 위한 배열의 크기
typedef int Element;            // 큐 요소의 자료형
#include "CircularQueue.h"      // 큐의 ADT 포함(원형 큐)
void BFS(int v)
{
    init_queue();
    PrintVtx(v);
    visited[v] = 1;
    enqueue(v);
    while (!is_empty()) {
        v = dequeue();
        for (int w = 0; w < vsize; w++) 
        {
            if (adj[v][w] != 0 && visited[w] == 0) 
            {
                PrintVtx(w); // 정점 w 방문
                visited[w] = 1;
                enqueue(w);
            }
        }
    }
}
void main()
{
    int s = 0;  // 시작 정점 A

    reset_visited();
    printf("\nDFS(%c출발) ==> ", vdata[s]);
    DFS(s);

    reset_visited();
    printf("\nBFS(%c출발) ==> ", vdata[s]);
    BFS(s);
    printf("\n\n");
}
