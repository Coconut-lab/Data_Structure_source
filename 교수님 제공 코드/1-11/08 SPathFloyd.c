// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch08/SPathDijkstra.c

#include <stdio.h>
#include <stdlib.h>

#define MAX_VSIZE	100	// 최대 정점 수
typedef char VElement;	// VElement의 자료형 정의
#define INF		999

int vsize = 7;
VElement vdata[MAX_VSIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

// 가중치 INF --> 간선이 없음
int adj[MAX_VSIZE][MAX_VSIZE] = {
    {   0,  25, INF,  12, INF, INF, INF },
    {  25,   0,  10, INF,  15, INF, INF },
    { INF,  10,   0, INF, INF, INF,  16 },
    {  12, INF, INF,   0,  17,  37, INF },
    { INF,  15, INF,  17,   0,  19,  14 },
    { INF, INF, INF,  37,  19,   0,  42 },
    { INF, INF,  16, INF,  14,  42,   0 }
};


int	A[MAX_VSIZE][MAX_VSIZE];	// 최단경로 거리 행렬
void printA()
{
    printf("====================================\n");
    for (int i = 0; i<vsize; i++) {
	for (int j = 0; j<vsize; j++) {
	    if (A[i][j] == INF) printf(" INF ");
	    else printf("%4d ", A[i][j]);
	}
	printf("\n");
    }
}


//--------------------------------------------------------------------
// 코드 8.7 Floyd의 최단 경로

void Floyd()
{
    for (int i = 0; i<vsize; i++)
	for (int j = 0; j<vsize; j++)
	    A[i][j] = adj[i][j];

    for (int k = 0; k<vsize; k++) {
	for (int i = 0; i<vsize; i++)
	    for (int j = 0; j < vsize; j++) {
		if (A[i][k] + A[k][j] < A[i][j])
		    A[i][j] = A[i][k] + A[k][j];
	    }
	printA();		// 진행상황 출력용 
    }
}

void main()
{
    Floyd();
}