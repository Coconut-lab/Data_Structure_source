#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 방 정보를 저장하는 구조체
typedef struct Room {
    char name;               // 방 이름 (a, b, c, d, e)
    int size;               // 방 크기 (평방미터)
    char description[50];   // 방 설명
    int cleanTime;          // 예상 청소 시간 (분)
    struct Room* left;      // 왼쪽 자식
    struct Room* right;     // 오른쪽 자식
} Room;

// 청소 통계 구조체
typedef struct {
    int totalRooms;
    int totalSize;
    int totalTime;
    char fastestRoom;
    char slowestRoom;
} CleanStats;

// 선 출력 함수
void printLine(char ch, int count) {
    for (int i = 0; i < count; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

// 새로운 방 노드 생성
Room* createRoom(char name, int size, const char* desc) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) {
        printf("메모리 할당 실패!\n");
        return NULL;
    }

    newRoom->name = name;
    newRoom->size = size;
    strcpy(newRoom->description, desc);
    newRoom->cleanTime = size * 2;  // 1평방미터당 2분으로 계산
    newRoom->left = NULL;
    newRoom->right = NULL;

    return newRoom;
}

// 이진 탐색 트리에 방 추가 (크기 기준 정렬)
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

// 최적 청소 순서 출력 (중위 순회)
void printOptimalOrder(Room* root, int* order) {
    if (root != NULL) {
        printOptimalOrder(root->left, order);

        (*order)++;
        printf("%d순위: 방 %c (%s)\n", *order, root->name, root->description);
        printf("       크기: %d㎡, 예상시간: %d분\n\n", root->size, root->cleanTime);

        printOptimalOrder(root->right, order);
    }
}

// 청소 통계 계산
void calculateStats(Room* root, CleanStats* stats) {
    if (root == NULL) return;

    calculateStats(root->left, stats);

    stats->totalRooms++;
    stats->totalSize += root->size;
    stats->totalTime += root->cleanTime;

    // 가장 빠른/느린 방 찾기
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

// 가장 작은 방 찾기
Room* findSmallestRoom(Room* root) {
    if (root == NULL) return NULL;

    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 트리 메모리 해제
void freeTree(Room* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// 현재 시간 출력
void printCurrentTime() {
    time_t rawtime;
    struct tm* timeinfo;
    char timeStr[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("분석 시간: %s\n", timeStr);
}

// 청소 시뮬레이션
void simulateCleaning(Room* root) {
    if (root == NULL) return;

    simulateCleaning(root->left);

    printf("로봇이 방 %c 청소 중", root->name);
    fflush(stdout);

    // 간단한 로딩 애니메이션
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        // 시간 지연 효과
        for (int j = 0; j < 100000000; j++);
    }
    printf(" 완료!\n");

    simulateCleaning(root->right);
}

int main() {
    Room* root = NULL;
    CleanStats stats = {0, 0, 0, 'a', 'a'};
    char roomNames[5] = {'a', 'b', 'c', 'd', 'e'};
    char descriptions[5][50] = {
        "거실", "안방", "부엌", "화장실", "작은방"
    };

    printf("=== 스마트 로봇청소기 최적화 시스템 ===\n\n");
    printCurrentTime();
    printf("\n");

    // 각 방의 크기 입력받기
    printf("각 방의 크기를 입력하세요 (단위: ㎡):\n");
    for (int i = 0; i < 5; i++) {
        int size;
        printf("방 %c (%s)의 크기: ", roomNames[i], descriptions[i]);
        scanf("%d", &size);

        // 입력 검증
        if (size <= 0) {
            printf("잘못된 크기입니다. 다시 입력하세요.\n");
            i--; // 다시 입력받기
            continue;
        }

        root = insertRoom(root, roomNames[i], size, descriptions[i]);
    }

    printf("\n");
    printLine('=', 50);
    printf("=== 분석 결과 ===\n\n");

    // 최적 청소 순서 출력
    printf("최적 청소 순서 (효율성 기준):\n");
    printLine('-', 40);
    int order = 0;
    printOptimalOrder(root, &order);

    // 첫 번째 추천 방
    Room* firstRoom = findSmallestRoom(root);
    if (firstRoom != NULL) {
        printf("추천 시작 방: %c번 방 (%s)\n",
               firstRoom->name, firstRoom->description);
        printf("이유: 가장 작은 크기(%d㎡)로 빠른 성취감 획득\n\n",
               firstRoom->size);
    }

    // 통계 계산 및 출력
    calculateStats(root, &stats);
    printf("청소 통계:\n");
    printLine('-', 25);
    printf("총 방 개수: %d개\n", stats.totalRooms);
    printf("총 청소 면적: %d㎡\n", stats.totalSize);
    printf("예상 총 시간: %d분 (%.1f시간)\n",
           stats.totalTime, stats.totalTime / 60.0);
    printf("가장 빠른 방: %c번 방\n", stats.fastestRoom);
    printf("가장 느린 방: %c번 방\n\n", stats.slowestRoom);

    // 효율성 팁
    printf("효율성 팁:\n");
    printLine('-', 15);
    printf("1. 작은 방부터: 빠른 성취감과 동기부여\n");
    printf("2. 배터리 관리: 큰 방 전에 충전 상태 확인\n");
    printf("3. 장애물 제거: 미리 바닥 정리로 시간 단축\n");
    printf("4. 정기 청소: 더러움 정도에 따른 시간 조절\n\n");

    // 청소 시뮬레이션 선택
    char choice;
    printf("청소 시뮬레이션을 실행하시겠습니까? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        printf("\n청소 시뮬레이션 시작!\n");
        printLine('-', 30);
        simulateCleaning(root);
        printf("\n모든 방 청소 완료! 수고하셨습니다!\n");
    }

    // 메모리 해제
    freeTree(root);

    return 0;
}