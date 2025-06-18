/*
 * 이진 탐색 트리 구조
 * 방 크기 기준 정렬
 * 최적 순서 출력
 * 메모리 관리
 */

#include <stdio.h>
#include <stdlib.h>

// 방 정보를 저장하는 구조체
typedef struct Room {
    char name;              // 방 이름
    int size;              // 방 크기
    struct Room* left;     // 왼쪽 자식
    struct Room* right;    // 오른쪽 자식
} Room;

// 새로운 방 노드 생성
Room* createRoom(char name, int size) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) return NULL;

    newRoom->name = name;
    newRoom->size = size;
    newRoom->left = NULL;
    newRoom->right = NULL;
    return newRoom;
}

// 이진 탐색 트리에 방 추가 (크기 기준 정렬)
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

// 최적 청소 순서 출력 (중위 순회 - 작은 것부터)
void printOptimalOrder(Room* root) {
    if (root != NULL) {
        printOptimalOrder(root->left);
        printf("%c(%d) ", root->name, root->size);
        printOptimalOrder(root->right);
    }
}

// 가장 작은 방 찾기
Room* findSmallestRoom(Room* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 메모리 해제
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

    // 방 크기 입력
    printf("방 크기 입력 (a, b, c, d, e): ");
    for (int i = 0; i < 5; i++) {
        int size;
        scanf("%d", &size);
        root = insertRoom(root, roomNames[i], size);
    }

    // 결과 출력
    printf("최적 순서: ");
    printOptimalOrder(root);
    printf("\n");

    // 첫 번째 추천 방
    Room* first = findSmallestRoom(root);
    if (first != NULL) {
        printf("시작 방: %c\n", first->name);
    }

    // 메모리 해제
    freeTree(root);
    return 0;
}