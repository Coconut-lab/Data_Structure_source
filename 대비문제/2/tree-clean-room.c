#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 20

// 트리 노드 구조체
typedef struct Node {
    int room_id;
    struct Node* children[MAX_ROOMS];
    int child_count;
    struct Node* parent;
} Room;

// 경로 정보
typedef struct {
    int path[MAX_ROOMS * 2];
    int length;
    int total_moves;
} Path;

// 글로벌 변수
Room* rooms[MAX_ROOMS];
int room_count = 0;
int visited[MAX_ROOMS];
Path best_path;
int total_paths = 0;

// 방 생성
Room* create_room(int id) {
    Room* room = (Room*)malloc(sizeof(Room));
    room->room_id = id;
    room->child_count = 0;
    room->parent = NULL;

    for(int i = 0; i < MAX_ROOMS; i++) {
        room->children[i] = NULL;
    }

    rooms[room_count++] = room;
    return room;
}

// 방 연결
void connect_rooms(Room* parent, Room* child) {
    if(parent->child_count < MAX_ROOMS) {
        parent->children[parent->child_count++] = child;
        child->parent = parent;
    }
}

// 모든 방 방문 확인
int all_rooms_visited() {
    for(int i = 0; i < room_count; i++) {
        if(!visited[i]) return 0;
    }
    return 1;
}

// 모든 청소 경로 탐색 (수정된 버전)
void find_cleaning_paths(Room* current, Path* current_path, int moves) {
    current_path->path[current_path->length++] = current->room_id;
    visited[current->room_id] = 1;

    printf("현재 위치: %d, 방문한 방 수: %d/%d\n", current->room_id, current_path->length, room_count);
    fflush(stdout);

    if(all_rooms_visited()) {
        current_path->total_moves = moves;
        total_paths++;

        printf("경로 %d 발견: ", total_paths);
        for(int i = 0; i < current_path->length; i++) {
            printf("%d", current_path->path[i]);
            if(i < current_path->length - 1) printf("->");
        }
        printf(" (이동: %d회)\n", moves);
        fflush(stdout);

        // 최적 경로 업데이트
        if(best_path.total_moves == -1 || moves < best_path.total_moves) {
            best_path = *current_path;
        }
    } else {
        // 자식들 방문
        for(int i = 0; i < current->child_count; i++) {
            Room* child = current->children[i];
            if(!visited[child->room_id]) {
                find_cleaning_paths(child, current_path, moves + 1);
            }
        }

        // 부모로 이동 (아직 방문하지 않은 방이 있을 때)
        if(current->parent != NULL && !all_rooms_visited()) {
            find_cleaning_paths(current->parent, current_path, moves + 1);
        }
    }

    // 백트래킹
    current_path->length--;
    visited[current->room_id] = 0;
}

// 더 간단한 접근: 트리의 모든 노드를 DFS로 방문
void simple_dfs(Room* root, int* path, int* path_len, int* min_moves) {
    path[(*path_len)++] = root->room_id;

    for(int i = 0; i < root->child_count; i++) {
        simple_dfs(root->children[i], path, path_len, min_moves);
        if(i < root->child_count - 1) {
            // 다음 자식으로 가기 위해 부모로 돌아옴
            path[(*path_len)++] = root->room_id;
            (*min_moves)++;
        }
    }
}

// 집 구조 생성
void setup_house() {
    Room* room0 = create_room(0);  // 거실
    Room* room1 = create_room(1);  // 부엌
    Room* room2 = create_room(2);  // 침실1
    Room* room3 = create_room(3);  // 침실2
    Room* room4 = create_room(4);  // 화장실
    Room* room5 = create_room(5);  // 서재
    Room* room6 = create_room(6);  // 창고

    connect_rooms(room0, room1);
    connect_rooms(room0, room2);
    connect_rooms(room0, room3);
    connect_rooms(room1, room4);
    connect_rooms(room2, room5);
    connect_rooms(room3, room6);
}

// 메모리 해제
void cleanup() {
    for(int i = 0; i < room_count; i++) {
        free(rooms[i]);
    }
}

int main() {
    printf("프로그램 시작\n");
    fflush(stdout);

    setup_house();
    printf("집 구조 설정 완료. 총 방 개수: %d\n", room_count);
    fflush(stdout);

    // 방법 1: 간단한 DFS (트리 순회)
    printf("=== 간단한 트리 순회 ===\n");
    int simple_path[MAX_ROOMS * 2];
    int simple_path_len = 0;
    int simple_moves = 0;

    simple_dfs(rooms[0], simple_path, &simple_path_len, &simple_moves);

    printf("트리 순회 경로: ");
    for(int i = 0; i < simple_path_len; i++) {
        printf("%d", simple_path[i]);
        if(i < simple_path_len - 1) printf(" -> ");
    }
    printf("\n");
    printf("총 이동 횟수: %d\n", simple_path_len - 1);

    // 방법 2: 안전한 탐색 (제한된 경우의 수)
    printf("\n=== 제한된 탐색 ===\n");
    memset(visited, 0, sizeof(visited));
    best_path.total_moves = -1;
    total_paths = 0;

    Path current_path;
    current_path.length = 0;

    printf("안전한 탐색 시작...\n");
    fflush(stdout);

    find_cleaning_paths(rooms[0], &current_path, 0);

    printf("탐색된 경로 수: %d\n", total_paths);
    if(best_path.total_moves != -1) {
        printf("최적 이동 횟수: %d\n", best_path.total_moves);
        printf("최적 경로: ");
        for(int i = 0; i < best_path.length; i++) {
            printf("%d", best_path.path[i]);
            if(i < best_path.length - 1) printf(" -> ");
        }
        printf("\n");
    }

    fflush(stdout);
    cleanup();
    return 0;
}