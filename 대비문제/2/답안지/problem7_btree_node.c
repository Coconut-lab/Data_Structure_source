// ���� 7: B-Ʈ�� ��� ���� (������� ���)
// BTreeNode.h�� ����Ͽ� B-Ʈ���� ��� ������ �⺻ ���� ����

#include <stdio.h>
#include <stdlib.h>
#include "BTreeNode.h"

// ��� ������ ���ĵ� ��ġ�� Ű ����
void insert_key_in_node(BTreeNode* node, BTreeElement key) {
    if (is_btree_node_full(node)) {
        printf("��尡 ���� ��! Ű %d ���� ����\n", key);
        return;
    }
    
    // ������ ��ġ ã��
    int i = node->num_keys - 1;
    
    // Ű���� ���������� �̵���Ű�鼭 �ùٸ� ��ġ ã��
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    
    // Ű ����
    node->keys[i + 1] = key;
    node->num_keys++;
}

// ��忡�� Ư�� Ű ����
int remove_key_from_node(BTreeNode* node, BTreeElement key) {
    int index = -1;
    
    // ������ Ű ã��
    for (int i = 0; i < node->num_keys; i++) {
        if (node->keys[i] == key) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Ű %d�� ��忡�� ã�� �� ����\n", key);
        return 0;
    }
    
    // Ű ���� �� �������� �̵�
    for (int i = index; i < node->num_keys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    
    node->num_keys--;
    return 1;
}

// B-Ʈ������ Ű �˻� (BTreeNode.h�� ���� ���)
BTreeNode* search_btree(BTreeNode* root, BTreeElement key) {
    if (root == NULL) {
        return NULL;
    }
    
    int i = 0;
    
    // ���� ��忡�� Ű�� ã�ų� ������ �ڽ��� ã��
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }
    
    // Ű�� ã�� ���
    if (i < root->num_keys && key == root->keys[i]) {
        return root;
    }
    
    // ���� ��忡�� Ű�� ã�� ���� ���
    if (root->is_leaf) {
        return NULL;
    }
    
    // ������ �ڽ� ��忡�� ��� �˻�
    return search_btree(root->children[i], key);
}

// ����� ��� Ű ���
void print_btree_node(BTreeNode* node) {
    if (node == NULL) {
        printf("NULL ���");
        return;
    }
    
    printf("[");
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d", node->keys[i]);
        if (i < node->num_keys - 1) printf(", ");
    }
    printf("]");
    
    if (node->is_leaf) {
        printf(" (����)");
    } else {
        printf(" (����)");
    }
}

// B-Ʈ�� ��ü ��� (���� ����)
void print_btree(BTreeNode* root, int level) {
    if (root == NULL) return;
    
    // �鿩����� ���� ǥ��
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    
    printf("���� %d: ", level);
    print_btree_node(root);
    printf("\n");
    
    // �ڽ� ���� ���
    if (!root->is_leaf) {
        for (int i = 0; i <= root->num_keys; i++) {
            if (root->children[i] != NULL) {
                print_btree(root->children[i], level + 1);
            }
        }
    }
}

// ��� ���� (���� �� �����÷ο� ó��)
BTreeNode* split_node(BTreeNode* full_node) {
    printf("  ��� ���� ����\n");
    
    // BTreeNode.h�� create_btree_node ���
    BTreeNode* new_node = create_btree_node(full_node->is_leaf);
    if (new_node == NULL) return NULL;
    
    int mid = MAX_KEYS / 2;  // �߰� �ε���
    
    // ������ ������ Ű���� �� ���� �̵�
    for (int i = mid + 1; i < MAX_KEYS; i++) {
        new_node->keys[i - mid - 1] = full_node->keys[i];
        full_node->keys[i] = 0;  // ���� ��忡�� ����
    }
    new_node->num_keys = MAX_KEYS - mid - 1;
    
    // �ڽ� �����͵� �̵� (���� ����� ���)
    if (!full_node->is_leaf) {
        for (int i = mid + 1; i <= MAX_KEYS; i++) {
            new_node->children[i - mid - 1] = full_node->children[i];
            full_node->children[i] = NULL;
        }
    }
    
    // ���� ����� Ű ���� ����
    full_node->num_keys = mid;
    
    printf("  ���� �Ϸ�: �߰� Ű %d\n", full_node->keys[mid]);
    return new_node;
}

// B-Ʈ�� ���� �Լ�
int validate_btree(BTreeNode* root, BTreeElement min_key, BTreeElement max_key, int is_root) {
    if (root == NULL) return 1;  // �� Ʈ���� ��ȿ
    
    // Ű ���� ����
    if (!is_root && root->num_keys < MIN_KEYS) {
        printf("���� ����: Ű ���� ���� (%d < %d)\n", root->num_keys, MIN_KEYS);
        return 0;
    }
    
    if (root->num_keys > MAX_KEYS) {
        printf("���� ����: Ű ���� �ʰ� (%d > %d)\n", root->num_keys, MAX_KEYS);
        return 0;
    }
    
    // Ű ���� ���� ����
    for (int i = 0; i < root->num_keys - 1; i++) {
        if (root->keys[i] >= root->keys[i + 1]) {
            printf("���� ����: Ű ���� ���� ����\n");
            return 0;
        }
    }
    
    // �ڽ� ���� ��� ����
    if (!root->is_leaf) {
        for (int i = 0; i <= root->num_keys; i++) {
            BTreeElement child_min = (i == 0) ? min_key : root->keys[i - 1];
            BTreeElement child_max = (i == root->num_keys) ? max_key : root->keys[i];
            
            if (!validate_btree(root->children[i], child_min, child_max, 0)) {
                return 0;
            }
        }
    }
    
    return 1;  // ��ȿ�� B-Ʈ��
}

// �׽�Ʈ �Լ�
void test_btree_node() {
    // BTreeNode.h�� create_btree_node ���
    BTreeNode* root = create_btree_node(1);
    insert_key_in_node(root, 10);
    insert_key_in_node(root, 20);
    insert_key_in_node(root, 30);
    insert_key_in_node(root, 40);
    
    printf("���� ��: ");
    print_btree_node(root);
    printf("\n");
    
    // �˻� �׽�Ʈ
    printf("25 �˻�: %s\n", search_btree(root, 25) ? "�߰�" : "����");
    printf("20 �˻�: %s\n", search_btree(root, 20) ? "�߰�" : "����");
    
    // ��ȭ ���� Ȯ��
    printf("��� ������: %s\n", is_btree_node_full(root) ? "��" : "�ƴϿ�");
    
    // Ű ����
    remove_key_from_node(root, 30);
    printf("30 ���� ��: ");
    print_btree_node(root);
    printf("\n");
    
    // BTreeNode.h�� delete_btree ����Ͽ� �޸� ����
    delete_btree(root);
}

int main() {
    test_btree_node();
    return 0;
}
