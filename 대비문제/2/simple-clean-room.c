/*
 * ���� Ž�� Ʈ�� ����
 * �� ũ�� ���� ����
 * ���� ���� ���
 * �޸� ����
 */

#include <stdio.h>
#include <stdlib.h>

// �� ������ �����ϴ� ����ü
typedef struct Room {
    char name;              // �� �̸�
    int size;              // �� ũ��
    struct Room* left;     // ���� �ڽ�
    struct Room* right;    // ������ �ڽ�
} Room;

// ���ο� �� ��� ����
Room* createRoom(char name, int size) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) return NULL;

    newRoom->name = name;
    newRoom->size = size;
    newRoom->left = NULL;
    newRoom->right = NULL;
    return newRoom;
}

// ���� Ž�� Ʈ���� �� �߰� (ũ�� ���� ����)
Room* insertRoom(Room* root, char name, int size) {
    if (root == NULL) {
        return createRoom(name, size);
    }

    if (size < root->size) {
        root->left = insertRoom(root->left, name, size);
    } else {
        root->right = insertRoom(root->right, name, size);
    }
    return root;
}

// ���� û�� ���� ��� (���� ��ȸ - ���� �ͺ���)
void printOptimalOrder(Room* root) {
    if (root != NULL) {
        printOptimalOrder(root->left);
        printf("%c(%d) ", root->name, root->size);
        printOptimalOrder(root->right);
    }
}

// ���� ���� �� ã��
Room* findSmallestRoom(Room* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// �޸� ����
void freeTree(Room* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Room* root = NULL;
    char roomNames[5] = {'a', 'b', 'c', 'd', 'e'};

    // �� ũ�� �Է�
    printf("�� ũ�� �Է� (a, b, c, d, e): ");
    for (int i = 0; i < 5; i++) {
        int size;
        scanf("%d", &size);
        root = insertRoom(root, roomNames[i], size);
    }

    // ��� ���
    printf("���� ����: ");
    printOptimalOrder(root);
    printf("\n");

    // ù ��° ��õ ��
    Room* first = findSmallestRoom(root);
    if (first != NULL) {
        printf("���� ��: %c\n", first->name);
    }

    // �޸� ����
    freeTree(root);
    return 0;
}