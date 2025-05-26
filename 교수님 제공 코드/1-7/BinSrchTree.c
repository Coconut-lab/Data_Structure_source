// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch07/BinSrchTree.c


//--------------------------------------------------------------------
// �ڵ� 7.8 ���� Ž�� Ʈ���� ����� �׽�Ʈ ���α׷�


typedef int TElement;       // TElement�� �ڷ��� ����
#include "TreeLinked.h"     // TNode ����ü�� ��� ���� �Լ�
#define VisitNode(n) (printf("%d ", (n)->data))
#define KEY(n) (n->data)

// ����Ž��Ʈ�� Ž��
TNode* search_bst(TNode* root, int key)
{
    if (root == NULL) return NULL;
    if (KEY(root) == key) return root;
    else if (key < KEY(root))
        return search_bst(root->left, key);
    else
        return search_bst(root->right, key);
}

// ����Ž��Ʈ�� ����
void insert_bst(TNode* root, TNode* n)
{
    if (KEY(n) < KEY(root)) {
        if (root->left == NULL) root->left = n;
        else insert_bst(root->left, n);
    }
    else if (KEY(n) > KEY(root)) {
        if (root->right == NULL) root->right = n;
        else insert_bst(root->right, n);
    }
    else free(n);
}

// ����Ž��Ʈ�� ����
TNode* delete_bst(TNode* root, int key)
{
    TNode* n = root; // ������ ���
    TNode* parent = NULL; // ������ ����� �θ�
    while (n != NULL && key != KEY(n)) {
        parent = n;
        n = (key < KEY(n)) ? n->left : n->right;
    }
    if (n == NULL) return root; // ������ ��尡 ����

    // case 1: n�� �ܸ� ����� ���
    if ((n->left == NULL && n->right == NULL)) {
        if (parent == NULL) root = NULL;
        else {
            if (parent->left == n) parent->left = NULL;
            else parent->right = NULL;
        }
        free(n);
    }
    // case 2: n�� �ϳ��� �ڽĸ� ���� ���
    else if (n->left == NULL || n->right == NULL) {
        TNode* child = (n->left != NULL) ? n->left : n->right;
        if (n == root) root = child;
        else {
            if (parent->left == n) parent->left = child;
            else parent->right = child;
        }
        free(n);
    }
    // case 3: n�� ���� �ڽ��� ��� ���� ���
    else {
        TNode* succ = n->right;
        while (succ->left != NULL)
            succ = succ->left;
        n->data = succ->data;
        n->right = delete_bst(n->right, KEY(succ));
    }
    return root; // ��Ʈ�� ������ �� �����Ƿ�(case1�� case2����) ��Ʈ�� ��ȯ�ؾ� ��
}

void preorder(TNode* n)
{
    if (n != NULL) {
        VisitNode(n);
        preorder(n->left);
        preorder(n->right);
    }
}

// �׽�Ʈ ���α׷�: 10���� ��带 ������ �� Ž���� ���� ����
void main()
{
    int keys[] = { 35, 18, 7, 26, 12, 3, 68, 22, 30, 99 };

    // ���� ���� �׽�Ʈ
    TNode* root = create_tree(keys[0], NULL, NULL);
    for (int i = 1; i < 10; i++) {
        TNode* n = create_tree(keys[i], NULL, NULL);
        insert_bst(root, n);
        printf("\n ���� %2d: ", keys[i]);
        preorder(root);
    }
    printf("\n");

    // Ž�� ���� �׽�Ʈ
    TNode* n = search_bst(root, 26);
    printf("26 Ž��: %s\n", (n != NULL) ? "����" : "����");
    n = search_bst(root, 25);
    printf("25 Ž��: %s\n", (n != NULL) ? "����" : "����");

    // ���� ���� �׽�Ʈ
    root = delete_bst(root, 3);
    printf("\ncase1: < 3> ����: ");
    preorder(root);
    root = delete_bst(root, 68);
    printf("\ncase2: <68> ����: ");
    preorder(root);
    root = delete_bst(root, 18);
    printf("\ncase3: <18> ����: ");
    preorder(root);
    root = delete_bst(root, 35);
    printf("\ncase3: <35> root: ");
    preorder(root);
}
