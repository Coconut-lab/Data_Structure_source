// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch07/TreeLinked.c

#include <stdio.h>
#include <stdlib.h>

// ���� Ʈ���� ����� ǥ���� ���� ��� ����ü
typedef struct TNode {
	TElement        data;   // ��忡 ������ �ڷ�
	struct TNode*   left;   // ���� ���� Ʈ��
	struct TNode*   right;  // ������ ���� Ʈ��
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
        delete_tree(n->left);   // ���� ����Ʈ�� ����
        delete_tree(n->right);  // ������ ����Ʈ�� ����
        free(n);                // ���� ��� ����
    }
}
