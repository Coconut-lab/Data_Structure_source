// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch08/MSTKruskal.c

//--------------------------------------------------------------------
// �ڵ� Kruskal�� �ּҺ�� ����Ʈ��


#include <stdio.h>
#include <stdlib.h>


#define MAX_VSIZE	100	// �ִ� ���� ��
typedef char VElement;	// VElement�� �ڷ��� ����
#define PrintVtx(i)		(printf("%c  ", vdata[i]))
#define INF		9999

// ����ġ �׷��� ��: MST �׽�Ʈ��
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
// Union-Find�� ���� �����Ϳ� ����
int		parent[MAX_VSIZE];		// �� ����� �θ��� �ε���	
int		set_size;				// ��ü ������ ����	
void init_set(int nSets)
{
	set_size = nSets;
	for (int i = 0; i<nSets; i++)
		parent[i] = -1;			// �� ó������ ��� ������ ���� ������ ����	
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
#define MAX_HSIZE 100			// ��Ʈ�� ��带 ������ �迭�� ũ��
struct HeapNode {				// ���� ������ �׸��� �ڷ��� 
	int		key;
	int		v1;
	int		v2;
};
typedef struct HeapNode HNode;	// HNode�� �ڷ��� ����
#define Compare(n1,n2)	((n2.key) - (n1.key))
#include "HeapADT.h"			// ��Ʈ���� ADT(�����Ϳ� ����) ����

//----------------------------------------------------------------------------
// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷� 
void Kruskal()
{
	init_set(vsize);

	// ��� ������ �ּ� ���� �߰�
	init_heap();
	for (int i = 0; i<vsize - 1; i++)
		for (int j = i + 1; j<vsize; j++)
			if (adj[i][j] > 0 && adj[i][j] < INF) {	// ������ ������
				HNode e;
				e.key = adj[i][j];		// �� ��带 ����� ���� ���� 
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
			printf("���� �߰� : %c - %c (���:%d)\n",
				vdata[e.v1], vdata[e.v2], e.key);
			union_set(uset, vset);
			edgeAccepted++;
		}
		else
			printf("���� ���� : %c - %c\n",
				vdata[e.v1], vdata[e.v2]);
	}
}
void main()
{
	printf("MST By Kruskal's Algorithm\n");
	Kruskal();
}

