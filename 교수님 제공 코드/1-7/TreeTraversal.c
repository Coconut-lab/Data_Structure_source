// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch07/TreeTraversal.c


//--------------------------------------------------------------------
// 코드 7.2 이진 트리의 순회


#include <stdio.h>
#include <stdlib.h>
typedef char TElement;
typedef struct TNode {
    TElement data;
    struct TNode* left;
    struct TNode* right;
} TNode;

#define VisitNode(n) (printf("[%c] ", (n)->data))
void preorder(TNode* n)
{
    if (n != NULL) {
        VisitNode(n);
        preorder(n->left);
        preorder(n->right);
    }
}
//--------------------------------------------------------------------
// 코드 7.3 중첩된 괄호 표현을 위한 전위순회 함수
/*
void preorder(TNode* n)
{
    if (n != NULL) {
        printf("( ");
        printf("%c ", n->data);
        // VisitNode(n);
        preorder(n->left);
        preorder(n->right);
        printf(")");
    }
}
*/

void inorder(TNode* n)
{
    if (n != NULL) {
        inorder(n->left);
        VisitNode(n);
        inorder(n->right);
    }
}
void postorder(TNode* n)
{
    if (n != NULL) {
        postorder(n->left);
        postorder(n->right);
        VisitNode(n);
    }
}

#define MAX_SIZE 100            // 큐를 위한 배열의 크기
typedef TNode* Element;         // 큐 요소의 자료형
#include "CircularQueue.h"      // 원형 큐 코드 포함

void levelorder(TNode* root)
{
    if (root != NULL) {
        init_queue();
        enqueue(root);          // 루트 노드에서 시작
        while (!is_empty()) {   // 큐가 공백이 아니면 반복
            TNode* n = dequeue();
            if (n != NULL) {
                VisitNode(n);
                enqueue(n->left);
                enqueue(n->right);
            }
        }
    }
}

void main()
{
    TNode d = { 'D', NULL, NULL };
    TNode e = { 'E', NULL, NULL };
    TNode b = { 'B', &d, &e };
    TNode f = { 'F', NULL, NULL };
    TNode c = { 'C', &f, NULL };
    TNode a = { 'A', &b, &c };
    TNode* root = &a;

    printf("\n   In-Order : ");
    inorder(root);
    printf("\n  Pre-Order : ");
    preorder(root);
    printf("\n Post-Order : ");
    postorder(root);
    printf("\nLevel-Order : ");
    levelorder(root);
}
