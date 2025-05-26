// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch07/BSTSorting.c


//--------------------------------------------------------------------
// �ڵ� 7.9 ���� Ž�� Ʈ���� �̿��� ����
typedef float TElement; // TElement�� �ڷ��� ����


//--------------------------------------------------------------------
// �ڵ� 7.8�� 2�� ~ 76�� �ڵ� ����
#include "TreeLinked.h"     // TNode ����ü�� ��� ���� �Լ�
#define VisitNode(n) (printf("%d ", (int)((n)->data)))
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
TNode* delete_bst(TNode* root, TElement key)
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
//--------------------------------------------------------------------


int inorder(TNode* n, TElement arr[], int count)
{
    if (n != NULL) {
        count = inorder(n->left, arr, count);
        arr[count++] = KEY(n);
        count = inorder(n->right, arr, count);
    }
    return count; // �迭�� ������� ����� ����� ���� ��ȯ
}
void sort_by_bst(TElement data[], int len)
{
    TNode* root = create_tree(data[0], NULL, NULL);
    for (int i = 1; i < len; i++) {
        TNode* n = create_tree(data[i], NULL, NULL);
        insert_bst(root, n);
    }
    inorder(root, data, 0); // ������ȸ�� �̿��� �迭 ����
    delete_tree(root); // BST�� ��� ��� ����
}
void main()
{
    float data[] = { 35, 18, 7, 26, 12, 3, 68, 22, 30, 99 };
    int len = 10;

    printf("\n������: ");
    for (int i = 0; i < len; i++)
        printf("%4.1f ", data[i]);

    sort_by_bst(data, len);

    printf("\n������: ");
    for (int i = 0; i < len; i++)
        printf("%4.1f ", data[i]);
    printf("\n");
}
