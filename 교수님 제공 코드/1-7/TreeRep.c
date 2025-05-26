// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch07/TreeRep.c


//--------------------------------------------------------------------
// 코드 7.1 동적 할당을 이용한 트리의 생성과 해제


#include <stdio.h>
#include <stdlib.h>

typedef char TElement; // 트리 노드에 저장할 데이터의 자료형
typedef struct TNode {
    TElement data;
    struct TNode* left;
    struct TNode* right;
} TNode;

TNode* create_tree(TElement data, TNode* left, TNode* right)
{
    TNode* n = (TNode*)malloc(sizeof(TNode)); // 루트 노드
    n->data = data;     // 데이터 복사
    n->left = left;     // 왼쪽 서브 트리 연결
    n->right = right;   // 오른쪽 서브 트리 연결
    return n;           // 루트 노드 반환
}

void delete_tree(TNode* n)
{
    if (n != NULL) {
        delete_tree(n->left);   // 왼쪽 서브 트리 삭제
        delete_tree(n->right);  // 오른쪽 서브 트리 삭제
        free(n);                // 루트 노드 삭제
    }
}

void main()
{
    /* 그림 7.17(a) 트리 동적 생성 */
    TNode* d = create_tree('D', NULL, NULL);
    TNode* e = create_tree('E', NULL, NULL);
    TNode* b = create_tree('B', d, e);
    TNode* f = create_tree('F', NULL, NULL);
    TNode* c = create_tree('C', f, NULL);
    TNode* root1 = create_tree('A', b, c);

    /* 그림 7.17(b) 트리 동적 생성 */
    TNode* D = create_tree('D', NULL, NULL);
    TNode* C = create_tree('C', D, NULL);
    TNode* B = create_tree('B', C, NULL);
    TNode* root2 = create_tree('A', B, NULL);

    /* 트리 동적 해제 */
    delete_tree(root1);
    delete_tree(root2);
}

#ifdef XXX
// 괄호를 이용해 트리 출력(전위 순회)
void preorder(TNode* n)
{
	if (n != NULL) {
		printf("( ");
		printf("%c ", n->data);
		preorder(n->left);
		preorder(n->right);
		printf(") ");
	}
	else printf(". ");
}
#endif
