// 해쉬, 체이싱

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    char value[50];
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

int hash(int key) {
    return key % TABLE_SIZE;
}

HashTable* createTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void insert(HashTable* ht, int key, const char* value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        newNode->next = ht->table[index];
        ht->table[index] = newNode;
    }
}

char* search(HashTable* ht, int key) {
    int index = hash(key);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void display(HashTable* ht) {
    printf("\n해시 테이블:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* current = ht->table[i];
        while (current != NULL) {
            printf("(%d,%s) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable* ht = createTable();

    insert(ht, 5, "Apple");
    insert(ht, 15, "Banana");
    insert(ht, 25, "Cherry");
    insert(ht, 7, "Date");
    insert(ht, 17, "Elderberry");
    insert(ht, 12, "Fig");

    display(ht);

    printf("\n검색 결과:\n");
    printf("key 15: %s\n", search(ht, 15));
    printf("key 7: %s\n", search(ht, 7));
    printf("key 99: %s\n", search(ht, 99) ? search(ht, 99) : "Not found");

    return 0;
}