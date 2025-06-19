// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch08/GraphRepAL.c


//--------------------------------------------------------------------
// 코드 8.2 인접 리스트를 이용한 그래프 표현


#include <stdio.h>
#include <stdlib.h>

#define MAX_VSIZE 100   // 최대 정점 수
typedef char VElement;  // VElement의 자료형 정의
typedef struct GNode {
    int id;             // 인접 정점의 id
    struct GNode* link; // 다음 노드의 포인터
} GNode;

int vsize = 5;          // 정점의 수
VElement vdata[5] = { 'U', 'V', 'W', 'X', 'Y' };
GNode* adj[5] = { NULL, NULL, NULL, NULL, NULL };

GNode* prepend_node(GNode* head, int v)
{
    GNode* n = (GNode*)malloc(sizeof(GNode));
    n->id = v;
    n->link = head;
    return n;
}
void insert_edge(int u, int v)
{
    adj[u] = prepend_node(adj[u], v);
    adj[v] = prepend_node(adj[v], u);
}
int degree(int v)
{
    int count = 0;
    for (GNode* p = adj[v]; p != NULL; p = p->link)
        count++;
    return count;
}

void main()
{
    insert_edge(0, 1);
    insert_edge(0, 2);
    insert_edge(1, 2);
    insert_edge(1, 3);
    insert_edge(2, 4);

    printf("그래프의 인접리스트 표현\n");
    for (int i = 0; i < vsize; i++) {
        printf("정점 %c(차수=%d): ", vdata[i], degree(i));
        for (GNode* p = adj[i]; p != NULL; p = p->link)
            printf(" %c", vdata[p->id]);
        printf("\n");
    }
    // 연결 리스트를 동적으로 해제하는 코드를 추가하는 것이 좋음
}
