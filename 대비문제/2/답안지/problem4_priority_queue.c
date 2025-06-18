// 문제 4: 이진트리 기반 우선순위 큐 구현 (헤더파일 사용)
// TreeLinked.h를 사용하여 우선순위 큐 구현

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeLinked.h"

#define MAX_TASKS 100

// 우선순위와 데이터를 매핑하는 구조체
typedef struct {
    int priority;
    char data[20];
} Task;

// 전역 작업 배열 (우선순위를 키로 사용)
Task tasks[MAX_TASKS];
int task_count = 0;

// 작업 추가 함수
void add_task(int priority, char* data) {
    strcpy(tasks[task_count].data, data);
    tasks[task_count].priority = priority;
    task_count++;
}

// 우선순위로 작업 찾기
char* find_task_data(int priority) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].priority == priority) {
            return tasks[i].data;
        }
    }
    return "Unknown";
}

// 우선순위 큐에 원소 삽입 (TreeLinked.h의 TNode 사용)
void insert_pq(TNode** root, int priority, char* data) {
    // 작업 데이터를 전역 배열에 저장
    add_task(priority, data);
    
    // TreeLinked.h의 create_tree 함수 사용하여 노드 생성
    TNode* new_node = create_tree(priority, NULL, NULL);
    
    if (*root == NULL) {
        *root = new_node;
        return;
    }
    
    // BST 규칙에 따라 삽입 (priority를 키로 사용)
    TNode* current = *root;
    TNode* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        if (priority < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    // 적절한 위치에 삽입
    if (priority < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

// 최소 우선순위 노드 찾기 (가장 왼쪽 노드)
TNode* find_min_priority_node(TNode* root) {
    if (root == NULL) return NULL;
    
    while (root->left != NULL) {
        root = root->left;
    }
    
    return root;
}

// BST에서 노드 삭제 (TreeLinked.h 스타일)
TNode* delete_pq_node(TNode* root, int priority) {
    if (root == NULL) return root;
    
    if (priority < root->data) {
        root->left = delete_pq_node(root->left, priority);
    }
    else if (priority > root->data) {
        root->right = delete_pq_node(root->right, priority);
    }
    else {
        // 삭제할 노드를 찾은 경우
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            TNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TNode* temp = root->left;
            free(root);
            return temp;
        }
        else {
            // 두 자식이 모두 있는 경우
            TNode* successor = find_min_priority_node(root->right);
            root->data = successor->data;
            root->right = delete_pq_node(root->right, successor->data);
        }
    }
    
    return root;
}

// 가장 높은 우선순위 노드 추출
int extract_min_priority(TNode** root) {
    if (*root == NULL) {
        printf("우선순위 큐가 비어있습니다!\n");
        return -1;
    }
    
    TNode* min_node = find_min_priority_node(*root);
    if (min_node == NULL) return -1;
    
    int min_priority = min_node->data;
    
    // BST에서 해당 노드 삭제
    *root = delete_pq_node(*root, min_priority);
    
    return min_priority;
}

// 우선순위 순서로 출력 (중위순회)
void print_priority_queue(TNode* root) {
    if (root != NULL) {
        print_priority_queue(root->left);
        printf("  [우선순위 %d] %s\n", root->data, find_task_data(root->data));
        print_priority_queue(root->right);
    }
}

// 우선순위 큐가 비어있는지 확인
int is_pq_empty(TNode* root) {
    return root == NULL;
}

// 테스트 함수
void test_priority_queue() {
    TNode* root = NULL;  // TreeLinked.h의 TNode 사용
    
    // 삽입 테스트
    insert_pq(&root, 3, "작업C");
    insert_pq(&root, 1, "작업A");
    insert_pq(&root, 2, "작업B");
    insert_pq(&root, 5, "작업E");
    insert_pq(&root, 4, "작업D");
    
    printf("초기 상태:\n");
    print_priority_queue(root);
    
    // 최고 우선순위 추출 테스트
    int extracted1 = extract_min_priority(&root);
    if (extracted1 != -1) {
        printf("\n추출: [%d] %s\n", extracted1, find_task_data(extracted1));
    }
    
    int extracted2 = extract_min_priority(&root);
    if (extracted2 != -1) {
        printf("추출: [%d] %s\n", extracted2, find_task_data(extracted2));
    }
    
    printf("\n남은 작업:\n");
    print_priority_queue(root);
    
    // 모든 작업 추출
    printf("\n모든 작업 처리:\n");
    while (!is_pq_empty(root)) {
        int priority = extract_min_priority(&root);
        if (priority != -1) {
            printf("[%d] %s\n", priority, find_task_data(priority));
        }
    }
    
    // TreeLinked.h의 delete_tree 함수 사용하여 메모리 해제
    delete_tree(root);
}

int main() {
    test_priority_queue();
    return 0;
}
