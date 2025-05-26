// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch07/TreeBasicOp.c

#include <stdio.h>
#include <stdlib.h>

// 노드에 저장할 데이터의 자료형
typedef char TElement;

// 트리 노드 구조체
typedef struct BTNode {
	TElement		data;
	struct BTNode* left;
	struct BTNode* right;
} TNode;


//--------------------------------------------------------------------
// 코드 7.4 이진 트리의 노드 수 구하기

int count_node(TNode* n)
{
    if (n == NULL)
        return 0;
    else return 1 + count_node(n->left) + count_node(n->right);
}

//--------------------------------------------------------------------
// 알고리즘 7.6 이진 트리의 노드 수를 구하기(전역변수와 전위순회 이용)
int count = 0;
void count_node1(TNode* n)
{
    if (n != NULL) {
        count++;
        count_node1(n->left);
        count_node1(n->right);
    }
}

// 트리의 단말 노드 수
int count_leaf(TNode* n)
{
	if (n == NULL) return 0;
	if (n->left == NULL && n->right == NULL) return 1;
	else return count_leaf(n->left) + count_leaf(n->right);
}

//--------------------------------------------------------------------
// 코드 7.5 이진 트리의 높이 구하기

#define MAX(a,b) ((a)>(b) ? (a):(b))
int calc_height(TNode* n)
{
    if (n == NULL)
        return 0;
    else return 1 + MAX(calc_height(n->left), calc_height(n->right));
}

//--------------------------------------------------------------------
// 코드 7.6 이진트리를 좌우로 대칭시키기

void reverse(TNode* p) {
    if (p != NULL) {
        TNode* tmp = p->left;
        p->left = p->right;
        p->right = tmp;

        reverse(p->left);
        reverse(p->right);
    }
}

//--------------------------------------------------------------------
// 코드 7.7 노드의 레벨 구하기

int calc_level(TNode* n, TNode* key, int level) {
    if (n == NULL)
        return 0;           // 찾는 노드 key가 없음
    if (n == key)
        return level;       // 노드 key 찾음. level 반환

    int l = calc_level(n->left, key, level + 1);
    if (l > 0)
        return l;
    return calc_level(n->right, key, level + 1);
}


// 테스트 프로그램
void main()
{
	TNode d = { 'D', NULL, NULL };
	TNode e = { 'E', NULL, NULL };
	TNode b = { 'B', &d, &e };
	TNode f = { 'F', NULL, NULL };
	TNode c = { 'C', &f, NULL };
	TNode a = { 'A', &b, &c };
	TNode* root = &a;

	printf(" 노드의 개수 = %d\n", count_node(root));
    count_node1(root);
    printf(" 노드의 개수 = %d\n", count);
    printf(" 단말의 개수 = %d\n", count_leaf(root));
	printf(" 트리의 높이 = %d\n", calc_height(root));

    reverse(root);
    printf(" 노드의 개수 = %d\n", count_node(root));

    reverse(root);
    printf(" D의 레벨 = %d\n", calc_level(root, &d, 1));
    printf(" C의 레벨 = %d\n", calc_level(root, &c, 1));
    printf(" A의 레벨 = %d\n", calc_level(root, &a, 1));
}

