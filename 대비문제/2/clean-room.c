#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// �� ������ �����ϴ� ����ü
typedef struct Room {
    char name;               // �� �̸� (a, b, c, d, e)
    int size;               // �� ũ�� (������)
    char description[50];   // �� ����
    int cleanTime;          // ���� û�� �ð� (��)
    struct Room* left;      // ���� �ڽ�
    struct Room* right;     // ������ �ڽ�
} Room;

// û�� ��� ����ü
typedef struct {
    int totalRooms;
    int totalSize;
    int totalTime;
    char fastestRoom;
    char slowestRoom;
} CleanStats;

// �� ��� �Լ�
void printLine(char ch, int count) {
    for (int i = 0; i < count; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

// ���ο� �� ��� ����
Room* createRoom(char name, int size, const char* desc) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) {
        printf("�޸� �Ҵ� ����!\n");
        return NULL;
    }

    newRoom->name = name;
    newRoom->size = size;
    strcpy(newRoom->description, desc);
    newRoom->cleanTime = size * 2;  // 1�����ʹ� 2������ ���
    newRoom->left = NULL;
    newRoom->right = NULL;

    return newRoom;
}

// ���� Ž�� Ʈ���� �� �߰� (ũ�� ���� ����)
Room* insertRoom(Room* root, char name, int size, const char* desc) {
    if (root == NULL) {
        return createRoom(name, size, desc);
    }

    if (size < root->size) {
        root->left = insertRoom(root->left, name, size, desc);
    } else {
        root->right = insertRoom(root->right, name, size, desc);
    }

    return root;
}

// ���� û�� ���� ��� (���� ��ȸ)
void printOptimalOrder(Room* root, int* order) {
    if (root != NULL) {
        printOptimalOrder(root->left, order);

        (*order)++;
        printf("%d����: �� %c (%s)\n", *order, root->name, root->description);
        printf("       ũ��: %d��, ����ð�: %d��\n\n", root->size, root->cleanTime);

        printOptimalOrder(root->right, order);
    }
}

// û�� ��� ���
void calculateStats(Room* root, CleanStats* stats) {
    if (root == NULL) return;

    calculateStats(root->left, stats);

    stats->totalRooms++;
    stats->totalSize += root->size;
    stats->totalTime += root->cleanTime;

    // ���� ����/���� �� ã��
    static int minTime = 999, maxTime = 0;
    if (root->cleanTime < minTime) {
        minTime = root->cleanTime;
        stats->fastestRoom = root->name;
    }
    if (root->cleanTime > maxTime) {
        maxTime = root->cleanTime;
        stats->slowestRoom = root->name;
    }

    calculateStats(root->right, stats);
}

// ���� ���� �� ã��
Room* findSmallestRoom(Room* root) {
    if (root == NULL) return NULL;

    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Ʈ�� �޸� ����
void freeTree(Room* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// ���� �ð� ���
void printCurrentTime() {
    time_t rawtime;
    struct tm* timeinfo;
    char timeStr[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("�м� �ð�: %s\n", timeStr);
}

// û�� �ùķ��̼�
void simulateCleaning(Room* root) {
    if (root == NULL) return;

    simulateCleaning(root->left);

    printf("�κ��� �� %c û�� ��", root->name);
    fflush(stdout);

    // ������ �ε� �ִϸ��̼�
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        // �ð� ���� ȿ��
        for (int j = 0; j < 100000000; j++);
    }
    printf(" �Ϸ�!\n");

    simulateCleaning(root->right);
}

int main() {
    Room* root = NULL;
    CleanStats stats = {0, 0, 0, 'a', 'a'};
    char roomNames[5] = {'a', 'b', 'c', 'd', 'e'};
    char descriptions[5][50] = {
        "�Ž�", "�ȹ�", "�ξ�", "ȭ���", "������"
    };

    printf("=== ����Ʈ �κ�û�ұ� ����ȭ �ý��� ===\n\n");
    printCurrentTime();
    printf("\n");

    // �� ���� ũ�� �Է¹ޱ�
    printf("�� ���� ũ�⸦ �Է��ϼ��� (����: ��):\n");
    for (int i = 0; i < 5; i++) {
        int size;
        printf("�� %c (%s)�� ũ��: ", roomNames[i], descriptions[i]);
        scanf("%d", &size);

        // �Է� ����
        if (size <= 0) {
            printf("�߸��� ũ���Դϴ�. �ٽ� �Է��ϼ���.\n");
            i--; // �ٽ� �Է¹ޱ�
            continue;
        }

        root = insertRoom(root, roomNames[i], size, descriptions[i]);
    }

    printf("\n");
    printLine('=', 50);
    printf("=== �м� ��� ===\n\n");

    // ���� û�� ���� ���
    printf("���� û�� ���� (ȿ���� ����):\n");
    printLine('-', 40);
    int order = 0;
    printOptimalOrder(root, &order);

    // ù ��° ��õ ��
    Room* firstRoom = findSmallestRoom(root);
    if (firstRoom != NULL) {
        printf("��õ ���� ��: %c�� �� (%s)\n",
               firstRoom->name, firstRoom->description);
        printf("����: ���� ���� ũ��(%d��)�� ���� ���밨 ȹ��\n\n",
               firstRoom->size);
    }

    // ��� ��� �� ���
    calculateStats(root, &stats);
    printf("û�� ���:\n");
    printLine('-', 25);
    printf("�� �� ����: %d��\n", stats.totalRooms);
    printf("�� û�� ����: %d��\n", stats.totalSize);
    printf("���� �� �ð�: %d�� (%.1f�ð�)\n",
           stats.totalTime, stats.totalTime / 60.0);
    printf("���� ���� ��: %c�� ��\n", stats.fastestRoom);
    printf("���� ���� ��: %c�� ��\n\n", stats.slowestRoom);

    // ȿ���� ��
    printf("ȿ���� ��:\n");
    printLine('-', 15);
    printf("1. ���� �����: ���� ���밨�� ����ο�\n");
    printf("2. ���͸� ����: ū �� ���� ���� ���� Ȯ��\n");
    printf("3. ��ֹ� ����: �̸� �ٴ� ������ �ð� ����\n");
    printf("4. ���� û��: ������ ������ ���� �ð� ����\n\n");

    // û�� �ùķ��̼� ����
    char choice;
    printf("û�� �ùķ��̼��� �����Ͻðڽ��ϱ�? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        printf("\nû�� �ùķ��̼� ����!\n");
        printLine('-', 30);
        simulateCleaning(root);
        printf("\n��� �� û�� �Ϸ�! �����ϼ̽��ϴ�!\n");
    }

    // �޸� ����
    freeTree(root);

    return 0;
}