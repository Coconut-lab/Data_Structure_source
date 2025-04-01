#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep 함수 사용을 위한 헤더

#define MAX_DISKS 8
#define TOWER_WIDTH 7
#define DISK_CHAR '*'

// 3개의 기둥 A, B, C를 표현하는 배열
int towers[3][MAX_DISKS];
int heights[3] = {0, 0, 0}; // 각 기둥에 쌓인 원판의 개수
int total_disks;
int move_count = 0;

// 원판 초기화 함수
void initialize_towers(int num_disks) {
    total_disks = num_disks;

    // 모든 타워 초기화
    for (int i = 0; i < 3; i++) {
        heights[i] = 0;
        for (int j = 0; j < MAX_DISKS; j++) {
            towers[i][j] = 0;
        }
    }

    // A 타워에 원판 쌓기 (크기가 큰 원판이 아래에 오도록)
    for (int i = num_disks; i >= 1; i--) {
        towers[0][heights[0]++] = i;
    }
}

// 화면 지우기 함수 (시스템 명령어 사용)
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// 현재 하노이 탑 상태 출력 함수
void display_towers() {
    clear_screen();
    printf("\n===== 하노이 탑 시각화 (%d번째 이동) =====\n\n", move_count);

    // 원판 출력 (위에서부터 그리기)
    for (int height = total_disks - 1; height >= 0; height--) {
        for (int tower = 0; tower < 3; tower++) {
            int disk_size = 0;

            // 해당 위치에 원판이 있는지 확인
            if (height < heights[tower]) {
                disk_size = towers[tower][height];
            }

            // 원판 그리기
            int spaces_before = (TOWER_WIDTH - disk_size) / 2;
            int spaces_after = TOWER_WIDTH - spaces_before - disk_size;

            printf("%*s", spaces_before, "");  // 왼쪽 공백

            if (disk_size > 0) {
                for (int i = 0; i < disk_size; i++) {
                    printf("%c", DISK_CHAR);
                }
            } else {
                // 원판이 없으면 기둥만 표시
                printf("|");
            }

            printf("%*s", spaces_after, "");  // 오른쪽 공백
            printf("   ");  // 기둥 사이 간격
        }
        printf("\n");
    }

    // 기둥 받침대 그리기
    for (int tower = 0; tower < 3; tower++) {
        for (int i = 0; i < TOWER_WIDTH; i++) {
            printf("=");
        }
        printf("   ");
    }
    printf("\n");

    // 기둥 이름 표시
    printf("   A      B      C   \n\n");
}

// 원판 이동 함수
void move_disk(int from, int to) {
    if (heights[from] <= 0) {
        printf("오류: 기둥 %c에는 원판이 없습니다.\n", 'A' + from);
        return;
    }

    // 원판 이동
    int disk = towers[from][--heights[from]];
    towers[to][heights[to]++] = disk;

    move_count++;
    display_towers();

    // 원판 이동을 시각적으로 볼 수 있도록 잠시 멈춤
    usleep(500000);  // 0.5초 대기 (마이크로초 단위)
}

// 하노이 탑 이동 알고리즘 (시각화 포함)
void hanoi_tower_visual(int n, int from, int via, int to) {
    if (n == 1) {
        printf("원판 1: %c --> %c\n", 'A' + from, 'A' + to);
        move_disk(from, to);
    } else {
        hanoi_tower_visual(n - 1, from, to, via);
        printf("원판 %d: %c --> %c\n", n, 'A' + from, 'A' + to);
        move_disk(from, to);
        hanoi_tower_visual(n - 1, via, from, to);
    }
}

int main() {
    int num_disks;

    printf("원판의 개수를 입력하세요 (1-%d): ", MAX_DISKS);
    scanf("%d", &num_disks);

    if (num_disks < 1 || num_disks > MAX_DISKS) {
        printf("원판 개수는 1에서 %d 사이여야 합니다.\n", MAX_DISKS);
        return 1;
    }

    initialize_towers(num_disks);
    display_towers();  // 초기 상태 표시

    printf("하노이 탑 시작. 아무 키나 누르세요...\n");
    getchar();  // 입력 버퍼 비우기
    getchar();  // 사용자 입력 대기

    // 하노이 탑 알고리즘 실행 (A->C, B를 경유)
    hanoi_tower_visual(num_disks, 0, 1, 2);

    printf("\n하노이 탑 완성! 총 %d번 이동했습니다.\n", move_count);

    return 0;
}