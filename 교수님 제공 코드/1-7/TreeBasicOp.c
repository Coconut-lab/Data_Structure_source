// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch07/TreeBasicOp.c

#include <stdio.h>
#include <stdlib.h>

// ��忡 ������ �������� �ڷ���
typedef char TElement;

// Ʈ�� ��� ����ü
typedef struct BTNode {
	TElement		data;
	struct BTNode* left;
	struct BTNode* right;
} TNode;


//--------------------------------------------------------------------
// �ڵ� 7.4 ���� Ʈ���� ��� �� ���ϱ�

int count_node(TNode* n)
{
    if (n == NULL)
        return 0;
    else return 1 + count_node(n->left) + count_node(n->right);
}

//--------------------------------------------------------------------
// �˰��� 7.6 ���� Ʈ���� ��� ���� ���ϱ�(���������� ������ȸ �̿�)
int count = 0;
void count_node1(TNode* n)
{
    if (n != NULL) {
        count++;
        count_node1(n->left);
        count_node1(n->right);
    }
}

// Ʈ���� �ܸ� ��� ��
int count_leaf(TNode* n)
{
	if (n == NULL) return 0;
	if (n->left == NULL && n->right == NULL) return 1;
	else return count_leaf(n->left) + count_leaf(n->right);
}

//--------------------------------------------------------------------
// �ڵ� 7.5 ���� Ʈ���� ���� ���ϱ�

#define MAX(a,b) ((a)>(b) ? (a):(b))
int calc_height(TNode* n)
{
    if (n == NULL)
        return 0;
    else return 1 + MAX(calc_height(n->left), calc_height(n->right));
}

//--------------------------------------------------------------------
// �ڵ� 7.6 ����Ʈ���� �¿�� ��Ī��Ű��

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
// �ڵ� 7.7 ����� ���� ���ϱ�

int calc_level(TNode* n, TNode* key, int level) {
    if (n == NULL)
        return 0;           // ã�� ��� key�� ����
    if (n == key)
        return level;       // ��� key ã��. level ��ȯ

    int l = calc_level(n->left, key, level + 1);
    if (l > 0)
        return l;
    return calc_level(n->right, key, level + 1);
}


// �׽�Ʈ ���α׷�
void main()
{
	TNode d = { 'D', NULL, NULL };
	TNode e = { 'E', NULL, NULL };
	TNode b = { 'B', &d, &e };
	TNode f = { 'F', NULL, NULL };
	TNode c = { 'C', &f, NULL };
	TNode a = { 'A', &b, &c };
	TNode* root = &a;

	printf(" ����� ���� = %d\n", count_node(root));
    count_node1(root);
    printf(" ����� ���� = %d\n", count);
    printf(" �ܸ��� ���� = %d\n", count_leaf(root));
	printf(" Ʈ���� ���� = %d\n", calc_height(root));

    reverse(root);
    printf(" ����� ���� = %d\n", count_node(root));

    reverse(root);
    printf(" D�� ���� = %d\n", calc_level(root, &d, 1));
    printf(" C�� ���� = %d\n", calc_level(root, &c, 1));
    printf(" A�� ���� = %d\n", calc_level(root, &a, 1));
}

