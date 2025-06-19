// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch08/SPathDijkstra.c


//--------------------------------------------------------------------
// 코드 8.6 Dijkstra의 최단 경로


#include <stdio.h>
#include <stdlib.h>
#define MAX_VSIZE 100   // 최대 정점 수
typedef char VElement;  // 정점의 자료형
#define INF 999         // 가중치의 무한대

int vsize = 7;
VElement vdata[MAX_VSIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
int adj[MAX_VSIZE][MAX_VSIZE] = {
    { 0, 25, INF, 12, INF, INF, INF },
    { 25, 0, 10, INF, 15, INF, INF },
    { INF, 10, 0, INF, INF, INF, 16 },
    { 12, INF, INF, 0, 17, 37, INF },
    { INF, 15, INF, 17, 0, 19, 14 },
    { INF, INF, INF, 37, 19, 0, 42 },
    { INF, INF, 16, INF, 14, 42, 0 }
};

int selected[MAX_VSIZE];    // S에 포함 여부 저장
int dist[MAX_VSIZE];        // 최단 거리 배열

int getMinVertex()
{
    int minv = 0, mindist = INF;
    for (int v = 0; v < vsize; v++)
        if (!selected[v] && dist[v] < mindist) {
            mindist = dist[v];
            minv = v;
        }
    return minv;
}
void print_step(int step)				// 진행 단계별 상황출력 
{
    printf(" Step%2d:", step);
    for (int i = 0; i < vsize; i++)
        if (dist[i] == INF) printf("  INF");
        else printf("%5d", dist[i]);
    printf("\n");
}

void Dijkstra(int start)
{
    for (int i = 0; i < vsize; i++) {
        selected[i] = 0;
        dist[i] = INF;
    }
    dist[start] = 0;                        // 시작 정점의 거리는 0

    for (int i = 0; i < vsize; i++) {
        int v = getMinVertex();             // v not in S 이고 dist가 최소인 정점
        selected[v] = 1;                    // v까지의 거리 확정
        for (int w = 0; w < vsize; w++) {
            if (selected[w] == 0)                   // w not in S
                if (dist[v] + adj[v][w] < dist[w])  // 갱신 조건
                    dist[w] = dist[v] + adj[v][w];
        }
        printf("%c 확정 ", vdata[v]);
        print_step(i);
    }
}
void main()
{
    Dijkstra(0);
}
