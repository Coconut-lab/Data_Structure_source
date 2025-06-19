// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch08/GraphSrchAM.c


//--------------------------------------------------------------------
// �ڵ� 8.3 �׷��� Ž��(���� ��� ǥ��)


#include <stdio.h>
#include <stdlib.h>
#define MAX_VSIZE 100   // �ִ� ���� ��
typedef char VElement;  // ������ �ڷ��� ����

int vsize = 8;          // �׷����� ���� ��
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

int visited[MAX_VSIZE]; // �湮 ǥ�� ����Ʈ
void reset_visited()
{
    for (int i = 0; i < vsize; i++)
        visited[i] = 0;
}
void DFS(int v)
{
    visited[v] = 1;
    PrintVtx(v); // ���� v �湮
    for (int w = 0; w < vsize; w++)
        if (adj[v][w] != 0 && visited[w] == 0)
            DFS(w);
}

#define MAX_SIZE 100            // ť ��Ҹ� ���� �迭�� ũ��
typedef int Element;            // ť ����� �ڷ���
#include "CircularQueue.h"      // ť�� ADT ����(���� ť)
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
                PrintVtx(w); // ���� w �湮
                visited[w] = 1;
                enqueue(w);
            }
        }
    }
}
void main()
{
    int s = 0;  // ���� ���� A

    reset_visited();
    printf("\nDFS(%c���) ==> ", vdata[s]);
    DFS(s);

    reset_visited();
    printf("\nBFS(%c���) ==> ", vdata[s]);
    BFS(s);
    printf("\n\n");
}
