// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch08/GraphSrchAL.c


//--------------------------------------------------------------------
// ���� ����Ʈ�� ǥ���� �׷����� Ž��(DFS, BFS)

//--------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define MAX_VSIZE	100	    // �ִ� ���� ��
typedef char VElement;	    // VElement�� �ڷ��� ����
typedef struct GNode {      // ���� ����Ʈ�� ���
    int	id;					// ������ id 
    struct GNode* link;		// ���� ����� ������ 
} GNode;

int vsize = 0;				// ��ü ������ ���� 
VElement vdata[MAX_VSIZE];	// ������ ������ ������ �迭 
GNode* adj[MAX_VSIZE];		// ������ ���� ����Ʈ 

// �׷����� �����  
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

// ������ �߰��ϴ� ����
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

// ������ �߰��ϴ� ����
void insert_edge_dir(int u, int v, int val)
{
    // ������ ��ȿ�� �˻� �ڵ� �߰�
    GNode* n = (GNode*)malloc(sizeof(GNode));
    n->id = v;
    n->link = adj[u];
    adj[u] = n;
}
void insert_edge(int u, int v, int val)
{
    // ������ ��ȿ�� �˻� �ڵ� �߰�
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
// �ڵ� 8.4 �׷��� Ž��(���� ����Ʈ ǥ��)

void DFS(int v) {
	PrintVtx(v);
	visited[v] = 1;
	for (GNode* p = adj[v]; p != NULL; p = p->link)
		if (visited[p->id] == 0)
			DFS(p->id);
}


#define MAX_SIZE 100		// ť ��� ������ ���� �迭�� ũ��
typedef int Element;		// ť�� Element �ڷ��� ����
#include "CircularQueue.h"  // ť�� ADT ����(���� ť)

//--------------------------------------------------------------------
// �ڵ� 8.4 �׷��� Ž��(���� ����Ʈ ǥ��)
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
		printf("DFS(%c���) ==> ", vdata[i]);
		DFS(i);
		printf("\n");

		reset_visited();
		printf("BFS(%c���) ==> ", vdata[i]);
		BFS(i);
		printf("\n\n");
	}
}
