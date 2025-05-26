// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch07/BSTSorting.c


//--------------------------------------------------------------------
// 코드 7.9 이진 탐색 트리를 이용한 정렬
typedef float TElement; // TElement의 자료형 정의


//--------------------------------------------------------------------
// 코드 7.8의 2행 ~ 76행 코드 삽입
#include "TreeLinked.h"     // TNode 구조체와 노드 생성 함수
#define VisitNode(n) (printf("%d ", (int)((n)->data)))
#define KEY(n) (n->data)

// 이진탐색트리 탐색
TNode* search_bst(TNode* root, int key)
{
    if (root == NULL) return NULL;
    if (KEY(root) == key) return root;
    else if (key < KEY(root))
        return search_bst(root->left, key);
    else
        return search_bst(root->right, key);
}

// 이진탐색트리 삽입
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

// 이진탐색트리 삭제
TNode* delete_bst(TNode* root, TElement key)
{
    TNode* n = root; // 삭제할 노드
    TNode* parent = NULL; // 삭제할 노드의 부모
    while (n != NULL && key != KEY(n)) {
        parent = n;
        n = (key < KEY(n)) ? n->left : n->right;
    }
    if (n == NULL) return root; // 삭제할 노드가 없음
    // case 1: n이 단말 노드인 경우
    if ((n->left == NULL && n->right == NULL)) {
        if (parent == NULL) root = NULL;
        else {
            if (parent->left == n) parent->left = NULL;
            else parent->right = NULL;
        }
        free(n);
    }
    // case 2: n이 하나의 자식만 갖는 경우
    else if (n->left == NULL || n->right == NULL) {
        TNode* child = (n->left != NULL) ? n->left : n->right;
        if (n == root) root = child;
        else {
            if (parent->left == n) parent->left = child;
            else parent->right = child;
        }
        free(n);
    }
    // case 3: n이 양쪽 자식을 모두 갖는 경우
    else {
        TNode* succ = n->right;
        while (succ->left != NULL)
            succ = succ->left;
        n->data = succ->data;
        n->right = delete_bst(n->right, KEY(succ));
    }
    return root; // 루트도 삭제될 수 있으므로(case1과 case2에서) 루트를 반환해야 함
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
    return count; // 배열에 현재까지 저장된 요소의 수를 반환
}
void sort_by_bst(TElement data[], int len)
{
    TNode* root = create_tree(data[0], NULL, NULL);
    for (int i = 1; i < len; i++) {
        TNode* n = create_tree(data[i], NULL, NULL);
        insert_bst(root, n);
    }
    inorder(root, data, 0); // 중위순회를 이용한 배열 정렬
    delete_tree(root); // BST의 모든 노드 삭제
}
void main()
{
    float data[] = { 35, 18, 7, 26, 12, 3, 68, 22, 30, 99 };
    int len = 10;

    printf("\n정렬전: ");
    for (int i = 0; i < len; i++)
        printf("%4.1f ", data[i]);

    sort_by_bst(data, len);

    printf("\n정렬후: ");
    for (int i = 0; i < len; i++)
        printf("%4.1f ", data[i]);
    printf("\n");
}
