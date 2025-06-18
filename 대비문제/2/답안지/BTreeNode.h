// B-트리 노드 구조 헤더 파일
// BTreeNode.h (TreeLinked.h를 확장하여 제작)

#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 4        // 최대 키 개수 (차수 5인 B-트리)
#define MAX_CHILDREN 5    // 최대 자식 개수
#define MIN_KEYS 2        // 최소 키 개수 (루트 제외)

typedef int BTreeElement;  // B-트리 원소의 자료형

// TreeLinked.h의 아이디어를 확장한 B-트리 노드 구조체
typedef struct BTreeNode {
    BTreeElement keys[MAX_KEYS];                    // 키 배열
    struct BTreeNode* children[MAX_CHILDREN];       // 자식 포인터 배열
    int num_keys;                                   // 현재 키 개수
    int is_leaf;                                    // 리프 노드 여부
} BTreeNode;

// TreeLinked.h의 create_tree를 참고하여 B-트리 노드 생성
BTreeNode* create_btree_node(int is_leaf) {
    BTreeNode* new_node = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (new_node == NULL) {
        printf("메모리 할당 실패!\n");
        return NULL;
    }
    
    new_node->num_keys = 0;
    new_node->is_leaf = is_leaf;
    
    // 키 배열 초기화
    for (int i = 0; i < MAX_KEYS; i++) {
        new_node->keys[i] = 0;
    }
    
    // 자식 포인터 배열 초기화
    for (int i = 0; i < MAX_CHILDREN; i++) {
        new_node->children[i] = NULL;
    }
    
    return new_node;
}

// TreeLinked.h의 delete_tree를 참고하여 B-트리 메모리 해제
void delete_btree(BTreeNode* root) {
    if (root != NULL) {
        // 자식 노드들 먼저 해제
        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                delete_btree(root->children[i]);
            }
        }
        free(root);
    }
}

// 노드가 가득 찼는지 확인
int is_btree_node_full(BTreeNode* node) {
    return node->num_keys == MAX_KEYS;
}

// 노드가 최소 키 개수를 만족하는지 확인
int is_btree_node_minimal(BTreeNode* node) {
    return node->num_keys == MIN_KEYS;
}
