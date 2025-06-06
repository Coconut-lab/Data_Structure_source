// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch10/avl_tree.c

#include <stdio.h> 
#include <stdlib.h> 

typedef int TElem;

typedef struct BinTrNode {
	TElem			data;
	struct BinTrNode*	left;
	struct BinTrNode*	right;
} TNode;

TNode* create_node(TElem val, TNode* l, TNode* r)
{
	TNode* n = (TNode*)malloc(sizeof(TNode));
	n->data = val;
	n->left = l;
	n->right = r;
	return n;
}

// 전위 순회를 이용한 트리 출력 함수.
// (루트(왼쪽서브트리)(오른쪽서브트리)) 형태로 출력함
void preorder(TNode* n)
{
	if (n != NULL) {
		printf("(");
		printf("%d ", n->data);
		preorder(n->left);
		preorder(n->right);
		printf(")");
	}
}

TNode* search_BST(TNode* root, int key)
{
	if (root == NULL)
		return NULL;

	if (root->data == key)
		return root;
	else if (key < root->data)
		return search_BST(root->left, key);
	else
		return search_BST(root->right, key);
}

int calc_height(TNode* n)
{
    if (n == NULL) return 0;

    int lh = calc_height(n->left);
    int rh = calc_height(n->right);
    return (lh > rh) ? lh + 1 : rh + 1;
}

//--------------------------------------------------------------------
// 코드 10.7 AVL 트리 삽입 연산의 구현

int calc_balance(TNode* n) { // 균형 인수 계산: BF = 왼쪽 높이 - 오른쪽 높이
    if (n == NULL) return 0;
    else return calc_height(n->left) - calc_height(n->right);
}
TNode* rotateLL(TNode* A) {
    TNode* B = A->left;
    A->left = B->right;
    B->right = A;
    return B;
}
TNode* rotateRR(TNode* A) {
    TNode* B = A->right;
    A->right = B->left;
    B->left = A;
    return B;
}
TNode* rotateRL(TNode* A) {
    TNode* B = A->right;
    A->right = rotateLL(B);
    return rotateRR(A);
}
TNode* rotateLR(TNode* A) {
    TNode* B = A->left;
    A->left = rotateRR(B);
    return rotateLL(A);
}

TNode* insert_AVL(TNode* root, int key) // AVL 트리의 삽입
{
    if (root == NULL)                   // 공백 노드 --> 노드 생성
        return create_node(key, NULL, NULL);
    if (key < root->data)
        root->left = insert_AVL(root->left, key);
    else if (key > root->data)
        root->right = insert_AVL(root->right, key);
    else return root;                   // 동일한 키는 허용하지 않음

    int balance = calc_balance(root);   // 균형 인수 계산: balance = lh - rh

    if (balance > 1) {                  // 왼쪽에 노드가 삽입되어 불균형 발생
        if (key < root->left->data)     // 왼쪽의 왼쪽에 삽입: LL
            return rotateLL(root);
        else return rotateLR(root);     // 왼쪽의 오른쪽에 삽입: LR
    }
    else if (balance < -1) {            // 오른쪽에 노드가 삽입되어 불균형 발생
        if (key < root->right->data)    // 오른쪽의 왼쪽에 삽입: RL
            return rotateRL(root);
        else return rotateRR(root);     // 오른쪽의 오른쪽에 삽입: RR
    }
    return root;                        // 루트 노드를 반환함
}


void main()
{
	TNode* root = NULL, * node;
//	int keys[] = { 7, 8, 9, 2, 1, 5, 3, 6, 4 }; // 그림 10.27의 데이터 삽입
	int keys[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 정렬된 데이터의 삽입

	for (int i = 0; i < 9; i++) {
		root = insert_AVL(root, keys[i]);
		printf("\n  삽입%2d: ", keys[i]);
		preorder(root);
	}
	printf("\n");
	printf(" 트리의 균형인수 = %d\n", calc_balance(root));

	// 탐색 연산 테스트 
	node = search_BST(root, 9);
	printf(" 9 탐색: %s\n", (node != NULL) ? "성공" : "실패");
	node = search_BST(root, 10);
	printf("10 탐색: %s\n", (node != NULL) ? "성공" : "실패");
}