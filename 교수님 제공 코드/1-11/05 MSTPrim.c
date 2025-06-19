// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch08/MSTPrim.c


//--------------------------------------------------------------------
// �ڵ� 8.5 Prim�� �ּҺ�� ����Ʈ��


#include <stdio.h>
#include <stdlib.h>

#define MAX_VSIZE 100   // �ִ� ���� ��
typedef char VElement;  // ������ �ڷ��� ����
#define INF 9999        // ���Ѵ�. ����ġ�� INF�̸� ������ ���� ������ ó��
#define InsertVtx(i) (printf("%c ", vdata[i])) // ���� i�� MST�� �߰��ϴ� �Լ�

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
int selected[MAX_VSIZE]; // MST ���� ����
int dist[MAX_VSIZE]; // MST���� �ִ� �Ÿ�
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
    for (int i = 0; i < vsize; i++) {       // vsize���� ������ �߰��ϸ� �Ϸ�
        int v = getMinVertex();
        selected[v] = 1;
        if (dist[v] == INF)                 // ���� ��Ȳ: ���� �׷����� �ƴ�
            return;
        InsertVtx(v);                       // ���õ� ������ MST�� �߰�
        for (int w = 0; w < vsize; w++)     // ���� ������ ����
            if (!selected[w])               // w not in MST
                if (adj[v][w] < dist[w])    // ���� ����
                    dist[w] = adj[v][w];
    }
    printf("\n");
}
void main()
{
    printf("MST By Prim's Algorithm\n");
    Prim();
}
