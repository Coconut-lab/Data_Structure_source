// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch08/MSTKruskal.c

//--------------------------------------------------------------------
// 코드 Kruskal의 최소비용 신장트리


#include <stdio.h>
#include <stdlib.h>


#define MAX_VSIZE	100	// 최대 정점 수
typedef char VElement;	// VElement의 자료형 정의
#define PrintVtx(i)		(printf("%c  ", vdata[i]))
#define INF		9999

// 가중치 그래프 예: MST 테스트용
int vsize = 7;
VElement vdata[MAX_VSIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
int adj[MAX_VSIZE][MAX_VSIZE] = {
    {   0,  29, INF, INF, INF,  10, INF },
    {  29,   0,  16, INF, INF, INF,  15 },
    { INF,  16,   0,  12, INF, INF, INF },
    { INF, INF,  12,   0,  22, INF,  18 },
    { INF, INF, INF,  22,   0,  27,  25 },
    {  10, INF, INF, INF,  27,   0, INF },
    { INF,  15, INF,  18,  25, INF,   0 }
};

//----------------------------------------------------------------------------
// Union-Find를 위한 데이터와 연산
int		parent[MAX_VSIZE];		// 각 노드의 부모노드 인덱스	
int		set_size;				// 전체 집합의 개수	
void init_set(int nSets)
{
	set_size = nSets;
	for (int i = 0; i<nSets; i++)
		parent[i] = -1;			// 맨 처음에는 모든 정점이 각각 고유의 집합	
}
int find_set(int id)
{
	while (parent[id] >= 0) id = parent[id];
	return id;
}
void union_set(int s1, int s2)
{
	parent[s1] = s2;
	set_size--;
}

//----------------------------------------------------------------------------
#define MAX_HSIZE 100			// 힙트리 노드를 저장할 배열의 크기
struct HeapNode {				// 힙에 저장할 항목의 자료형 
	int		key;
	int		v1;
	int		v2;
};
typedef struct HeapNode HNode;	// HNode의 자료형 정의
#define Compare(n1,n2)	((n2.key) - (n1.key))
#include "HeapADT.h"			// 힙트리의 ADT(데이터와 연산) 포함

//----------------------------------------------------------------------------
// kruskal의 최소 비용 신장 트리 프로그램 
void Kruskal()
{
	init_set(vsize);

	// 모든 간선을 최소 힙에 추가
	init_heap();
	for (int i = 0; i<vsize - 1; i++)
		for (int j = i + 1; j<vsize; j++)
			if (adj[i][j] > 0 && adj[i][j] < INF) {	// 간선이 있으면
				HNode e;
				e.key = adj[i][j];		// 힙 노드를 만들어 힙에 삽입 
				e.v1 = i;
				e.v2 = j;
				heap_push(e);
			}

	int edgeAccepted = 0;
	while (edgeAccepted < vsize - 1) {
		HNode e = heap_pop();
		int uset = find_set(e.v1);
		int vset = find_set(e.v2);

		if (uset != vset) {
			printf("간선 추가 : %c - %c (비용:%d)\n",
				vdata[e.v1], vdata[e.v2], e.key);
			union_set(uset, vset);
			edgeAccepted++;
		}
		else
			printf("간선 무시 : %c - %c\n",
				vdata[e.v1], vdata[e.v2]);
	}
}
void main()
{
	printf("MST By Kruskal's Algorithm\n");
	Kruskal();
}

