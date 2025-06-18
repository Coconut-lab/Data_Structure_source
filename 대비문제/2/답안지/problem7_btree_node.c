// 문제 7: B-트리 노드 구현 (헤더파일 사용)
// BTreeNode.h를 사용하여 B-트리의 노드 구조와 기본 연산 구현

#include <stdio.h>
#include <stdlib.h>
#include "BTreeNode.h"

// 노드 내에서 정렬된 위치에 키 삽입
void insert_key_in_node(BTreeNode* node, BTreeElement key) {
    if (is_btree_node_full(node)) {
        printf("노드가 가득 참! 키 %d 삽입 실패\n", key);
        return;
    }
    
    // 삽입할 위치 찾기
    int i = node->num_keys - 1;
    
    // 키들을 오른쪽으로 이동시키면서 올바른 위치 찾기
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    
    // 키 삽입
    node->keys[i + 1] = key;
    node->num_keys++;
}

// 노드에서 특정 키 제거
int remove_key_from_node(BTreeNode* node, BTreeElement key) {
    int index = -1;
    
    // 제거할 키 찾기
    for (int i = 0; i < node->num_keys; i++) {
        if (node->keys[i] == key) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("키 %d를 노드에서 찾을 수 없음\n", key);
        return 0;
    }
    
    // 키 제거 후 왼쪽으로 이동
    for (int i = index; i < node->num_keys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    
    node->num_keys--;
    return 1;
}

// B-트리에서 키 검색 (BTreeNode.h의 구조 사용)
BTreeNode* search_btree(BTreeNode* root, BTreeElement key) {
    if (root == NULL) {
        return NULL;
    }
    
    int i = 0;
    
    // 현재 노드에서 키를 찾거나 적절한 자식을 찾기
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }
    
    // 키를 찾은 경우
    if (i < root->num_keys && key == root->keys[i]) {
        return root;
    }
    
    // 리프 노드에서 키를 찾지 못한 경우
    if (root->is_leaf) {
        return NULL;
    }
    
    // 적절한 자식 노드에서 재귀 검색
    return search_btree(root->children[i], key);
}

// 노드의 모든 키 출력
void print_btree_node(BTreeNode* node) {
    if (node == NULL) {
        printf("NULL 노드");
        return;
    }
    
    printf("[");
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d", node->keys[i]);
        if (i < node->num_keys - 1) printf(", ");
    }
    printf("]");
    
    if (node->is_leaf) {
        printf(" (리프)");
    } else {
        printf(" (내부)");
    }
}

// B-트리 전체 출력 (레벨 순서)
void print_btree(BTreeNode* root, int level) {
    if (root == NULL) return;
    
    // 들여쓰기로 레벨 표현
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    
    printf("레벨 %d: ", level);
    print_btree_node(root);
    printf("\n");
    
    // 자식 노드들 출력
    if (!root->is_leaf) {
        for (int i = 0; i <= root->num_keys; i++) {
            if (root->children[i] != NULL) {
                print_btree(root->children[i], level + 1);
            }
        }
    }
}

// 노드 분할 (삽입 시 오버플로우 처리)
BTreeNode* split_node(BTreeNode* full_node) {
    printf("  노드 분할 시작\n");
    
    // BTreeNode.h의 create_btree_node 사용
    BTreeNode* new_node = create_btree_node(full_node->is_leaf);
    if (new_node == NULL) return NULL;
    
    int mid = MAX_KEYS / 2;  // 중간 인덱스
    
    // 오른쪽 절반의 키들을 새 노드로 이동
    for (int i = mid + 1; i < MAX_KEYS; i++) {
        new_node->keys[i - mid - 1] = full_node->keys[i];
        full_node->keys[i] = 0;  // 기존 노드에서 제거
    }
    new_node->num_keys = MAX_KEYS - mid - 1;
    
    // 자식 포인터도 이동 (내부 노드인 경우)
    if (!full_node->is_leaf) {
        for (int i = mid + 1; i <= MAX_KEYS; i++) {
            new_node->children[i - mid - 1] = full_node->children[i];
            full_node->children[i] = NULL;
        }
    }
    
    // 기존 노드의 키 개수 조정
    full_node->num_keys = mid;
    
    printf("  분할 완료: 중간 키 %d\n", full_node->keys[mid]);
    return new_node;
}

// B-트리 검증 함수
int validate_btree(BTreeNode* root, BTreeElement min_key, BTreeElement max_key, int is_root) {
    if (root == NULL) return 1;  // 빈 트리는 유효
    
    // 키 개수 검증
    if (!is_root && root->num_keys < MIN_KEYS) {
        printf("검증 실패: 키 개수 부족 (%d < %d)\n", root->num_keys, MIN_KEYS);
        return 0;
    }
    
    if (root->num_keys > MAX_KEYS) {
        printf("검증 실패: 키 개수 초과 (%d > %d)\n", root->num_keys, MAX_KEYS);
        return 0;
    }
    
    // 키 정렬 순서 검증
    for (int i = 0; i < root->num_keys - 1; i++) {
        if (root->keys[i] >= root->keys[i + 1]) {
            printf("검증 실패: 키 정렬 순서 오류\n");
            return 0;
        }
    }
    
    // 자식 노드들 재귀 검증
    if (!root->is_leaf) {
        for (int i = 0; i <= root->num_keys; i++) {
            BTreeElement child_min = (i == 0) ? min_key : root->keys[i - 1];
            BTreeElement child_max = (i == root->num_keys) ? max_key : root->keys[i];
            
            if (!validate_btree(root->children[i], child_min, child_max, 0)) {
                return 0;
            }
        }
    }
    
    return 1;  // 유효한 B-트리
}

// 테스트 함수
void test_btree_node() {
    // BTreeNode.h의 create_btree_node 사용
    BTreeNode* root = create_btree_node(1);
    insert_key_in_node(root, 10);
    insert_key_in_node(root, 20);
    insert_key_in_node(root, 30);
    insert_key_in_node(root, 40);
    
    printf("삽입 후: ");
    print_btree_node(root);
    printf("\n");
    
    // 검색 테스트
    printf("25 검색: %s\n", search_btree(root, 25) ? "발견" : "없음");
    printf("20 검색: %s\n", search_btree(root, 20) ? "발견" : "없음");
    
    // 포화 상태 확인
    printf("노드 가득참: %s\n", is_btree_node_full(root) ? "예" : "아니오");
    
    // 키 제거
    remove_key_from_node(root, 30);
    printf("30 제거 후: ");
    print_btree_node(root);
    printf("\n");
    
    // BTreeNode.h의 delete_btree 사용하여 메모리 해제
    delete_btree(root);
}

int main() {
    test_btree_node();
    return 0;
}
