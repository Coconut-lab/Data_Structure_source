// ���� 4: ����Ʈ�� ��� �켱���� ť ���� (������� ���)
// TreeLinked.h�� ����Ͽ� �켱���� ť ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeLinked.h"

#define MAX_TASKS 100

// �켱������ �����͸� �����ϴ� ����ü
typedef struct {
    int priority;
    char data[20];
} Task;

// ���� �۾� �迭 (�켱������ Ű�� ���)
Task tasks[MAX_TASKS];
int task_count = 0;

// �۾� �߰� �Լ�
void add_task(int priority, char* data) {
    strcpy(tasks[task_count].data, data);
    tasks[task_count].priority = priority;
    task_count++;
}

// �켱������ �۾� ã��
char* find_task_data(int priority) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].priority == priority) {
            return tasks[i].data;
        }
    }
    return "Unknown";
}

// �켱���� ť�� ���� ���� (TreeLinked.h�� TNode ���)
void insert_pq(TNode** root, int priority, char* data) {
    // �۾� �����͸� ���� �迭�� ����
    add_task(priority, data);
    
    // TreeLinked.h�� create_tree �Լ� ����Ͽ� ��� ����
    TNode* new_node = create_tree(priority, NULL, NULL);
    
    if (*root == NULL) {
        *root = new_node;
        return;
    }
    
    // BST ��Ģ�� ���� ���� (priority�� Ű�� ���)
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
    
    // ������ ��ġ�� ����
    if (priority < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

// �ּ� �켱���� ��� ã�� (���� ���� ���)
TNode* find_min_priority_node(TNode* root) {
    if (root == NULL) return NULL;
    
    while (root->left != NULL) {
        root = root->left;
    }
    
    return root;
}

// BST���� ��� ���� (TreeLinked.h ��Ÿ��)
TNode* delete_pq_node(TNode* root, int priority) {
    if (root == NULL) return root;
    
    if (priority < root->data) {
        root->left = delete_pq_node(root->left, priority);
    }
    else if (priority > root->data) {
        root->right = delete_pq_node(root->right, priority);
    }
    else {
        // ������ ��带 ã�� ���
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
            // �� �ڽ��� ��� �ִ� ���
            TNode* successor = find_min_priority_node(root->right);
            root->data = successor->data;
            root->right = delete_pq_node(root->right, successor->data);
        }
    }
    
    return root;
}

// ���� ���� �켱���� ��� ����
int extract_min_priority(TNode** root) {
    if (*root == NULL) {
        printf("�켱���� ť�� ����ֽ��ϴ�!\n");
        return -1;
    }
    
    TNode* min_node = find_min_priority_node(*root);
    if (min_node == NULL) return -1;
    
    int min_priority = min_node->data;
    
    // BST���� �ش� ��� ����
    *root = delete_pq_node(*root, min_priority);
    
    return min_priority;
}

// �켱���� ������ ��� (������ȸ)
void print_priority_queue(TNode* root) {
    if (root != NULL) {
        print_priority_queue(root->left);
        printf("  [�켱���� %d] %s\n", root->data, find_task_data(root->data));
        print_priority_queue(root->right);
    }
}

// �켱���� ť�� ����ִ��� Ȯ��
int is_pq_empty(TNode* root) {
    return root == NULL;
}

// �׽�Ʈ �Լ�
void test_priority_queue() {
    TNode* root = NULL;  // TreeLinked.h�� TNode ���
    
    // ���� �׽�Ʈ
    insert_pq(&root, 3, "�۾�C");
    insert_pq(&root, 1, "�۾�A");
    insert_pq(&root, 2, "�۾�B");
    insert_pq(&root, 5, "�۾�E");
    insert_pq(&root, 4, "�۾�D");
    
    printf("�ʱ� ����:\n");
    print_priority_queue(root);
    
    // �ְ� �켱���� ���� �׽�Ʈ
    int extracted1 = extract_min_priority(&root);
    if (extracted1 != -1) {
        printf("\n����: [%d] %s\n", extracted1, find_task_data(extracted1));
    }
    
    int extracted2 = extract_min_priority(&root);
    if (extracted2 != -1) {
        printf("����: [%d] %s\n", extracted2, find_task_data(extracted2));
    }
    
    printf("\n���� �۾�:\n");
    print_priority_queue(root);
    
    // ��� �۾� ����
    printf("\n��� �۾� ó��:\n");
    while (!is_pq_empty(root)) {
        int priority = extract_min_priority(&root);
        if (priority != -1) {
            printf("[%d] %s\n", priority, find_task_data(priority));
        }
    }
    
    // TreeLinked.h�� delete_tree �Լ� ����Ͽ� �޸� ����
    delete_tree(root);
}

int main() {
    test_priority_queue();
    return 0;
}
