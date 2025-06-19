#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 20

// Ʈ�� ��� ����ü
typedef struct Node {
    int room_id;
    struct Node* children[MAX_ROOMS];
    int child_count;
    struct Node* parent;
} Room;

// ��� ����
typedef struct {
    int path[MAX_ROOMS * 2];
    int length;
    int total_moves;
} Path;

// �۷ι� ����
Room* rooms[MAX_ROOMS];
int room_count = 0;
int visited[MAX_ROOMS];
Path best_path;
int total_paths = 0;

// �� ����
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

// �� ����
void connect_rooms(Room* parent, Room* child) {
    if(parent->child_count < MAX_ROOMS) {
        parent->children[parent->child_count++] = child;
        child->parent = parent;
    }
}

// ��� �� �湮 Ȯ��
int all_rooms_visited() {
    for(int i = 0; i < room_count; i++) {
        if(!visited[i]) return 0;
    }
    return 1;
}

// ��� û�� ��� Ž�� (������ ����)
void find_cleaning_paths(Room* current, Path* current_path, int moves) {
    current_path->path[current_path->length++] = current->room_id;
    visited[current->room_id] = 1;

    printf("���� ��ġ: %d, �湮�� �� ��: %d/%d\n", current->room_id, current_path->length, room_count);
    fflush(stdout);

    if(all_rooms_visited()) {
        current_path->total_moves = moves;
        total_paths++;

        printf("��� %d �߰�: ", total_paths);
        for(int i = 0; i < current_path->length; i++) {
            printf("%d", current_path->path[i]);
            if(i < current_path->length - 1) printf("->");
        }
        printf(" (�̵�: %dȸ)\n", moves);
        fflush(stdout);

        // ���� ��� ������Ʈ
        if(best_path.total_moves == -1 || moves < best_path.total_moves) {
            best_path = *current_path;
        }
    } else {
        // �ڽĵ� �湮
        for(int i = 0; i < current->child_count; i++) {
            Room* child = current->children[i];
            if(!visited[child->room_id]) {
                find_cleaning_paths(child, current_path, moves + 1);
            }
        }

        // �θ�� �̵� (���� �湮���� ���� ���� ���� ��)
        if(current->parent != NULL && !all_rooms_visited()) {
            find_cleaning_paths(current->parent, current_path, moves + 1);
        }
    }

    // ��Ʈ��ŷ
    current_path->length--;
    visited[current->room_id] = 0;
}

// �� ������ ����: Ʈ���� ��� ��带 DFS�� �湮
void simple_dfs(Room* root, int* path, int* path_len, int* min_moves) {
    path[(*path_len)++] = root->room_id;

    for(int i = 0; i < root->child_count; i++) {
        simple_dfs(root->children[i], path, path_len, min_moves);
        if(i < root->child_count - 1) {
            // ���� �ڽ����� ���� ���� �θ�� ���ƿ�
            path[(*path_len)++] = root->room_id;
            (*min_moves)++;
        }
    }
}

// �� ���� ����
void setup_house() {
    Room* room0 = create_room(0);  // �Ž�
    Room* room1 = create_room(1);  // �ξ�
    Room* room2 = create_room(2);  // ħ��1
    Room* room3 = create_room(3);  // ħ��2
    Room* room4 = create_room(4);  // ȭ���
    Room* room5 = create_room(5);  // ����
    Room* room6 = create_room(6);  // â��

    connect_rooms(room0, room1);
    connect_rooms(room0, room2);
    connect_rooms(room0, room3);
    connect_rooms(room1, room4);
    connect_rooms(room2, room5);
    connect_rooms(room3, room6);
}

// �޸� ����
void cleanup() {
    for(int i = 0; i < room_count; i++) {
        free(rooms[i]);
    }
}

int main() {
    printf("���α׷� ����\n");
    fflush(stdout);

    setup_house();
    printf("�� ���� ���� �Ϸ�. �� �� ����: %d\n", room_count);
    fflush(stdout);

    // ��� 1: ������ DFS (Ʈ�� ��ȸ)
    printf("=== ������ Ʈ�� ��ȸ ===\n");
    int simple_path[MAX_ROOMS * 2];
    int simple_path_len = 0;
    int simple_moves = 0;

    simple_dfs(rooms[0], simple_path, &simple_path_len, &simple_moves);

    printf("Ʈ�� ��ȸ ���: ");
    for(int i = 0; i < simple_path_len; i++) {
        printf("%d", simple_path[i]);
        if(i < simple_path_len - 1) printf(" -> ");
    }
    printf("\n");
    printf("�� �̵� Ƚ��: %d\n", simple_path_len - 1);

    // ��� 2: ������ Ž�� (���ѵ� ����� ��)
    printf("\n=== ���ѵ� Ž�� ===\n");
    memset(visited, 0, sizeof(visited));
    best_path.total_moves = -1;
    total_paths = 0;

    Path current_path;
    current_path.length = 0;

    printf("������ Ž�� ����...\n");
    fflush(stdout);

    find_cleaning_paths(rooms[0], &current_path, 0);

    printf("Ž���� ��� ��: %d\n", total_paths);
    if(best_path.total_moves != -1) {
        printf("���� �̵� Ƚ��: %d\n", best_path.total_moves);
        printf("���� ���: ");
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