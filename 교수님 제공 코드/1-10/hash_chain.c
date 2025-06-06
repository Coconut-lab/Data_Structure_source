// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// �������� ch10/hash_chain.c


//--------------------------------------------------------------------
// �ڵ� 10.6 ü�̴�


#include <stdio.h>
#include <stdlib.h>
typedef int Entry;      // ���̺� ������ ��Ʈ��
typedef struct HNode {  // �ܼ� ���� ���
    Entry key;
    struct HNode* link;
} Node;

#define M   13          // �ؽ� ���̺��� ũ��
Node* table[M];         // �ؽ� ���̺�
int hashFn(Entry key) { return key % M; }

void init_chain() {     // ���̺� �ʱ�ȭ �Լ�
    for (int i = 0; i < M; i++) // ��� ��Ŷ�� NULL�� �ʱ�ȭ
        table[i] = NULL;
}
void print_chain(char* msg) {	// ���̺� ��� �Լ�
    printf("%s: ", msg);
    for (int i = 0; i < M; i++) {
        printf("->");
        for (Node* n = table[i]; n != NULL; n = n->link)
            printf("%2d ", n->key);
        printf(" ");
    }
    printf("\n");
}

void insert_chain(Entry key) {
    int i = hashFn(key);                    // �ؽ� �ּ� ���
    Node* n = (Node*)malloc(sizeof(Node));  // ��� ����
    n->key = key;                           // ��Ʈ�� ����
    n->link = table[i];                     // �� �տ� ����
    table[i] = n;
}

Node* search_chain(Entry key) {
    int i = hashFn(key);                    // �ؽ� �ּ� ���
    for (Node* n = table[i]; n != NULL; n = n->link)
        if (key == n->key)                  // Ž�� ����: ��� ��ȯ
            return n;
    return NULL;                            // Ž�� ����: NULL ��ȯ
}

void delete_chain(Entry key) {
    int i = hashFn(key);                    // �ؽ� �ּ� ���
    Node* n = table[i];                     // �ش� �ּ��� ���� ���
    if (n == NULL) return;                  // (1) ������ ��尡 ���� ���
    if (key == n->key) {                    // (2) ù ��° ��� ����
        table[i] = n->link;
        free(n);
    }
    else {                                  // (3) �� ��: ���� ��带 �˾ƾ� ��
        for (; n->link != NULL; n = n->link) {
            if (key == n->link->key) {
                Node* p = n->link;
                n->link = p->link;
                free(p);
                return;
            }
        }
    }
}


void main()
{
    Entry data[9] = { 45, 27, 88, 9, 71, 60, 46, 38, 24 };

    init_chain();
    print_chain("������");

    for (int i = 0; i < 9; i++) {
        insert_chain(data[i]);
        print_chain("      ");
    }

    printf("46Ž��: %p\n", search_chain(46));
    printf("39Ž��: %p\n", search_chain(39));

    delete_chain(60);	print_chain("60����");
    delete_chain(45);	print_chain("45����");
}
