// ���� 5: ���ڿ� �ؽ� ���̺� ����
// hash_chain.c�� �����Ͽ� ���ڿ��� Ű�� �ϴ� ����(Dictionary) ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hash_chain�� ���� Ȯ��
typedef struct DictNode {
    char key[50];      // ���ڿ� Ű
    char value[100];   // ���ڿ� ��
    struct DictNode* next;  // ���� ��� ������ (ü�̴�)
} DictNode;

#define DICT_SIZE 17    // �ؽ� ���̺� ũ�� (�Ҽ� ���)
DictNode* dictionary[DICT_SIZE];  // �ؽ� ���̺�

// �ؽ� ���̺� �ʱ�ȭ
void init_dictionary() {
    for (int i = 0; i < DICT_SIZE; i++) {
        dictionary[i] = NULL;
    }
}

// ���ڿ� �ؽ� �Լ� ����
// �� ������ ASCII ���� �̿��� �ؽ� �Լ�
int string_hash(char* str) {
    int hash_value = 0;
    int len = strlen(str);
    
    // ��� 1: ������ �ջ� ���
    for (int i = 0; i < len; i++) {
        hash_value += str[i];
    }
    
    // ��� 2: �� ���� �ؽ� �Լ� (ȣ���� ���)
    // hash_value = 0;
    // for (int i = 0; i < len; i++) {
    //     hash_value = (hash_value * 31 + str[i]) % DICT_SIZE;
    // }
    
    return hash_value % DICT_SIZE;
}

// ���ο� ��ųʸ� ��� ����
DictNode* create_dict_node(char* key, char* value) {
    DictNode* new_node = (DictNode*)malloc(sizeof(DictNode));
    if (new_node == NULL) {
        printf("�޸� �Ҵ� ����!\n");
        return NULL;
    }
    
    strcpy(new_node->key, key);
    strcpy(new_node->value, value);
    new_node->next = NULL;
    
    return new_node;
}

// ��ųʸ��� Ű-�� �� �߰�
// hash_chain�� insert_chain �����Ͽ� ����
void dict_put(char* key, char* value) {
    int index = string_hash(key);  // �ؽ� �ּ� ���
    
    // ������ ���� Ű�� �ִ��� Ȯ�� (������Ʈ ó��)
    DictNode* current = dictionary[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // ���� Ű �߰� - �� ������Ʈ
            strcpy(current->value, value);
    
            return;
        }
        current = current->next;
    }
    
    // ���ο� Ű-�� �� �߰� (ü���� �� �տ� ����)
    DictNode* new_node = create_dict_node(key, value);
    if (new_node == NULL) return;
    
    new_node->next = dictionary[index];  // ���� ü�� ����
    dictionary[index] = new_node;        // �� ��带 ���� ����
    

}

// ��ųʸ����� Ű�� �ش��ϴ� �� �˻�
// hash_chain�� search_chain �����Ͽ� ����
char* dict_get(char* key) {
    int index = string_hash(key);  // �ؽ� �ּ� ���
    
    // �ش� �ε����� ü���� ��ȸ�ϸ� �˻�
    DictNode* current = dictionary[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Ű �߰� - �� ��ȯ

            return current->value;
        }
        current = current->next;
    }
    
    // Ű�� ã�� ����

    return NULL;
}

// ��ųʸ����� Ű-�� �� ����
// hash_chain�� delete_chain �����Ͽ� ����
void dict_remove(char* key) {
    int index = string_hash(key);  // �ؽ� �ּ� ���
    DictNode* current = dictionary[index];
    
    if (current == NULL) {
    
        return;
    }
    
    // ù ��° ��尡 ���� ����� ���
    if (strcmp(current->key, key) == 0) {
        dictionary[index] = current->next;

        free(current);
        return;
    }
    
    // ������ ���� �߿��� ���� ��� ã��
    while (current->next != NULL) {
        if (strcmp(current->next->key, key) == 0) {
            DictNode* node_to_delete = current->next;
            current->next = node_to_delete->next;

            free(node_to_delete);
            return;
        }
        current = current->next;
    }
    

}

// Ư�� Ű�� �����ϴ��� Ȯ��
int dict_contains(char* key) {
    return dict_get(key) != NULL;
}

// ��ųʸ� ��ü ���
void print_dictionary() {
    printf("\n=== ��ųʸ� ��ü ���� ===\n");
    int total_items = 0;
    
    for (int i = 0; i < DICT_SIZE; i++) {
        printf("�ε��� %2d: ", i);
        
        DictNode* current = dictionary[i];
        if (current == NULL) {
            printf("(�������)\n");
        } else {
            while (current != NULL) {
                printf("[%s:%s]", current->key, current->value);
                if (current->next != NULL) printf(" -> ");
                current = current->next;
                total_items++;
            }
            printf("\n");
        }
    }
    
    printf("�� %d�� �׸�\n", total_items);
}

// �ؽ� ���̺� ��� ���
void print_hash_statistics() {
    int non_empty_buckets = 0;
    int max_chain_length = 0;
    int total_items = 0;
    
    for (int i = 0; i < DICT_SIZE; i++) {
        int chain_length = 0;
        DictNode* current = dictionary[i];
        
        while (current != NULL) {
            chain_length++;
            total_items++;
            current = current->next;
        }
        
        if (chain_length > 0) {
            non_empty_buckets++;
            if (chain_length > max_chain_length) {
                max_chain_length = chain_length;
            }
        }
    }
    
    printf("\n=== �ؽ� ���̺� ��� ===\n");
    printf("��ü ��Ŷ ��: %d\n", DICT_SIZE);
    printf("���� ��Ŷ ��: %d\n", non_empty_buckets);
    printf("�� �׸� ��: %d\n", total_items);
    printf("�ִ� ü�� ����: %d\n", max_chain_length);
    printf("������: %.2f\n", (double)total_items / DICT_SIZE);
}

// �޸� ����
void destroy_dictionary() {
    for (int i = 0; i < DICT_SIZE; i++) {
        DictNode* current = dictionary[i];
        while (current != NULL) {
            DictNode* temp = current;
            current = current->next;
            free(temp);
        }
        dictionary[i] = NULL;
    }
    printf("��ųʸ� �޸� ���� �Ϸ�\n");
}

// �׽�Ʈ �Լ�
void test_string_dictionary() {
    init_dictionary();
    
    // �⺻ ����
    dict_put("apple", "���");
    dict_put("banana", "�ٳ���");
    dict_put("cherry", "ü��");
    dict_put("grape", "����");
    dict_put("orange", "������");
    
    // �˻� �׽�Ʈ
    printf("�˻� ���:\n");
    printf("apple: %s\n", dict_get("apple"));
    printf("banana: %s\n", dict_get("banana"));
    
    // ������Ʈ
    dict_put("apple", "���� ���");
    printf("apple ������Ʈ: %s\n", dict_get("apple"));
    
    // ����
    dict_remove("banana");
    printf("banana ���� ��: %s\n", dict_get("banana") ? dict_get("banana") : "NULL");
    
    destroy_dictionary();
}

int main() {
    test_string_dictionary();
    return 0;
}
