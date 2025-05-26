// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch07/BinSrchTree.c


//--------------------------------------------------------------------
// 코드 7.8 이진 탐색 트리의 연산과 테스트 프로그램


typedef int TElement;       // TElement의 자료형 정의
#include "TreeLinked.h"     // TNode 구조체와 노드 생성 함수
#define VisitNode(n) (printf("%d ", (n)->data))
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
TNode* delete_bst(TNode* root, int key)
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

// 테스트 프로그램: 10개의 노드를 삽입한 후 탐색과 삭제 수행
void main()
{
    int keys[] = { 35, 18, 7, 26, 12, 3, 68, 22, 30, 99 };

    // 삽입 연산 테스트
    TNode* root = create_tree(keys[0], NULL, NULL);
    for (int i = 1; i < 10; i++) {
        TNode* n = create_tree(keys[i], NULL, NULL);
        insert_bst(root, n);
        printf("\n 삽입 %2d: ", keys[i]);
        preorder(root);
    }
    printf("\n");

    // 탐색 연산 테스트
    TNode* n = search_bst(root, 26);
    printf("26 탐색: %s\n", (n != NULL) ? "성공" : "실패");
    n = search_bst(root, 25);
    printf("25 탐색: %s\n", (n != NULL) ? "성공" : "실패");

    // 삭제 연산 테스트
    root = delete_bst(root, 3);
    printf("\ncase1: < 3> 삭제: ");
    preorder(root);
    root = delete_bst(root, 68);
    printf("\ncase2: <68> 삭제: ");
    preorder(root);
    root = delete_bst(root, 18);
    printf("\ncase3: <18> 삭제: ");
    preorder(root);
    root = delete_bst(root, 35);
    printf("\ncase3: <35> root: ");
    preorder(root);
}
