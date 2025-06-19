// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch08/GraphSrchAL.c


//--------------------------------------------------------------------
// 인접 리스트로 표현된 그래프의 탐색(DFS, BFS)

//--------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define MAX_VSIZE	100	    // 최대 정점 수
typedef char VElement;	    // VElement의 자료형 정의
typedef struct GNode {      // 인접 리스트의 노드
    int	id;					// 정점의 id 
    struct GNode* link;		// 다음 노드의 포인터 
} GNode;

int vsize = 0;				// 전체 정점의 개수 
VElement vdata[MAX_VSIZE];	// 정점에 저장할 데이터 배열 
GNode* adj[MAX_VSIZE];		// 정점의 인접 리스트 

// 그래프의 연산들  
int is_empty_graph() { return (vsize == 0); }
int is_full_graph() { return (vsize >= MAX_VSIZE); }
void init_graph()
{
    vsize = 0;
    for (int i = 0; i < MAX_VSIZE; i++)
        adj[i] = NULL;
}
void delete_graph()
{
    for (int i = 0; i < vsize; i++) {
        while (adj[i] != NULL) {
            GNode* n = adj[i];
            adj[i] = n->link;
            free(n);
        }
    }
    vsize = 0;
}

// 정점을 추가하는 연산
void append_vtx(VElement e)
{
    if (is_full_graph()) {
        printf("Overflow Error(vertex)\n");
        exit(0);
    }

    vdata[vsize] = e;
    adj[vsize] = NULL;
    vsize += 1;
}

// 간선을 추가하는 연산
void insert_edge_dir(int u, int v, int val)
{
    // 간선의 유효성 검사 코드 추가
    GNode* n = (GNode*)malloc(sizeof(GNode));
    n->id = v;
    n->link = adj[u];
    adj[u] = n;
}
void insert_edge(int u, int v, int val)
{
    // 간선의 유효성 검사 코드 추가
    insert_edge_dir(u, v, val);
    insert_edge_dir(v, u, val);
}
//----------------------------------------------------------------------------

#define PrintVtx(i)		(printf("%c  ", vdata[i]))

int	visited[MAX_VSIZE];
void reset_visited()
{
	for (int i = 0; i<vsize; i++)
		visited[i] = 0;
}


//--------------------------------------------------------------------
// 코드 8.4 그래프 탐색(인접 리스트 표현)

void DFS(int v) {
	PrintVtx(v);
	visited[v] = 1;
	for (GNode* p = adj[v]; p != NULL; p = p->link)
		if (visited[p->id] == 0)
			DFS(p->id);
}


#define MAX_SIZE 100		// 큐 요소 저장을 위한 배열의 크기
typedef int Element;		// 큐의 Element 자료형 정의
#include "CircularQueue.h"  // 큐의 ADT 포함(원형 큐)

//--------------------------------------------------------------------
// 코드 8.4 그래프 탐색(인접 리스트 표현)
void BFS(int v)
{
	init_queue();

	enqueue(v);
	visited[v] = 1;
	PrintVtx(v);
	while (!is_empty()) {
		v = dequeue();
		for (GNode* w = adj[v]; w != NULL; w = w->link) {
			if (!visited[w->id]) {
				enqueue(w->id);
				visited[w->id] = 1;
				PrintVtx(w->id);
			}
		}
	}
}

void main()
{
	VElement vtx[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	int am[MAX_VSIZE][MAX_VSIZE] = {
		{ 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 1, 0, 0, 0, 0 },
		{ 1, 0, 0, 1, 1, 0, 0, 0 },
		{ 0, 1, 1, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 1, 0 }
	};

	init_graph();
	for (int i = 0; i < 8; i++)
		append_vtx(vtx[i]);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if( am[i][j] )
				insert_edge_dir(i, j, 1);


	for (int i = 0; i < 3; i++) {
		reset_visited();
		printf("DFS(%c출발) ==> ", vdata[i]);
		DFS(i);
		printf("\n");

		reset_visited();
		printf("BFS(%c출발) ==> ", vdata[i]);
		BFS(i);
		printf("\n\n");
	}
}
