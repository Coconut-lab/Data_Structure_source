// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch08/MSTPrim.c


//--------------------------------------------------------------------
// 코드 8.5 Prim의 최소비용 신장트리


#include <stdio.h>
#include <stdlib.h>

#define MAX_VSIZE 100   // 최대 정점 수
typedef char VElement;  // 정점의 자료형 정의
#define INF 9999        // 무한대. 가중치가 INF이면 간선이 없는 것으로 처리
#define InsertVtx(i) (printf("%c ", vdata[i])) // 정점 i를 MST에 추가하는 함수

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
int selected[MAX_VSIZE]; // MST 포함 여부
int dist[MAX_VSIZE]; // MST와의 최단 거리
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
void Prim()
{
    for (int i = 0; i < vsize; i++) {
        dist[i] = INF;
        selected[i] = 0;
    }
    dist[0] = 0;
    for (int i = 0; i < vsize; i++) {       // vsize개의 정점을 추가하면 완료
        int v = getMinVertex();
        selected[v] = 1;
        if (dist[v] == INF)                 // 예외 상황: 연결 그래프가 아님
            return;
        InsertVtx(v);                       // 선택된 정점을 MST에 추가
        for (int w = 0; w < vsize; w++)     // 인접 정점에 대해
            if (!selected[w])               // w not in MST
                if (adj[v][w] < dist[w])    // 갱신 조건
                    dist[w] = adj[v][w];
    }
    printf("\n");
}
void main()
{
    printf("MST By Prim's Algorithm\n");
    Prim();
}
