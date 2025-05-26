// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch07/TreeLinked.c

#include <stdio.h>
#include <stdlib.h>

// 이진 트리의 연결된 표현을 위한 노드 구조체
typedef struct TNode {
	TElement        data;   // 노드에 저장할 자료
	struct TNode*   left;   // 왼쪽 서브 트리
	struct TNode*   right;  // 오른쪽 서브 트리
} TNode;

TNode* create_tree(TElement data, TNode* left, TNode* right)
{
    TNode* n = (TNode*)malloc(sizeof(TNode));
    n->data = data;
    n->left = left;
    n->right = right;
    return n;
}
void delete_tree(TNode* n)
{
    if (n != NULL) {
        delete_tree(n->left);   // 왼쪽 서브트리 삭제
        delete_tree(n->right);  // 오른쪽 서브트리 삭제
        free(n);                // 현재 노드 삭제
    }
}
