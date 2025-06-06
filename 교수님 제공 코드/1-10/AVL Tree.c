// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch10/avl_tree.c

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

// ���� ��ȸ�� �̿��� Ʈ�� ��� �Լ�.
// (��Ʈ(���ʼ���Ʈ��)(�����ʼ���Ʈ��)) ���·� �����
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
// �ڵ� 10.7 AVL Ʈ�� ���� ������ ����

int calc_balance(TNode* n) { // ���� �μ� ���: BF = ���� ���� - ������ ����
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

TNode* insert_AVL(TNode* root, int key) // AVL Ʈ���� ����
{
    if (root == NULL)                   // ���� ��� --> ��� ����
        return create_node(key, NULL, NULL);
    if (key < root->data)
        root->left = insert_AVL(root->left, key);
    else if (key > root->data)
        root->right = insert_AVL(root->right, key);
    else return root;                   // ������ Ű�� ������� ����

    int balance = calc_balance(root);   // ���� �μ� ���: balance = lh - rh

    if (balance > 1) {                  // ���ʿ� ��尡 ���ԵǾ� �ұ��� �߻�
        if (key < root->left->data)     // ������ ���ʿ� ����: LL
            return rotateLL(root);
        else return rotateLR(root);     // ������ �����ʿ� ����: LR
    }
    else if (balance < -1) {            // �����ʿ� ��尡 ���ԵǾ� �ұ��� �߻�
        if (key < root->right->data)    // �������� ���ʿ� ����: RL
            return rotateRL(root);
        else return rotateRR(root);     // �������� �����ʿ� ����: RR
    }
    return root;                        // ��Ʈ ��带 ��ȯ��
}


void main()
{
	TNode* root = NULL, * node;
//	int keys[] = { 7, 8, 9, 2, 1, 5, 3, 6, 4 }; // �׸� 10.27�� ������ ����
	int keys[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // ���ĵ� �������� ����

	for (int i = 0; i < 9; i++) {
		root = insert_AVL(root, keys[i]);
		printf("\n  ����%2d: ", keys[i]);
		preorder(root);
	}
	printf("\n");
	printf(" Ʈ���� �����μ� = %d\n", calc_balance(root));

	// Ž�� ���� �׽�Ʈ 
	node = search_BST(root, 9);
	printf(" 9 Ž��: %s\n", (node != NULL) ? "����" : "����");
	node = search_BST(root, 10);
	printf("10 Ž��: %s\n", (node != NULL) ? "����" : "����");
}