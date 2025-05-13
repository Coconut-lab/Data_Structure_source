#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep 함수 사용을 위한 헤더

/*
 * [프로그램 설명]
 * 이 프로그램은 하노이의 탑 문제를 시각적으로 보여주는 콘솔 기반 GUI 프로그램입니다.
 * 텍스트 문자를 사용하여 원반과 기둥을 표현하고, 원반이 움직이는 과정을 
 * 애니메이션처럼 보여줍니다.
 * 
 * [하노이의 탑]
 * 세 개의 기둥(A, B, C)과 크기가 다른 원반들로 구성됩니다.
 * 목표는 A 기둥에 있는 모든 원반을 C 기둥으로 옮기는 것입니다.
 * 규칙:
 * 1. 한 번에 하나의 원반만 이동 가능
 * 2. 큰 원반이 작은 원반 위에 있을 수 없음
 * 3. 임시로 B 기둥을 사용 가능
 */

#define MAX_DISKS 8        // 최대 원반 개수
#define TOWER_WIDTH 7      // 화면에 표시될 기둥의 폭
#define DISK_CHAR '*'      // 원반을 표시할 문자

// 3개의 기둥 A, B, C를 표현하는 배열
int towers[3][MAX_DISKS];  // 각 기둥에 쌓인 원반 크기 저장
int heights[3] = {0, 0, 0}; // 각 기둥에 쌓인 원반의 개수
int total_disks;           // 전체 원반 개수
int move_count = 0;        // 이동 횟수 카운터

/*
 * [함수: initialize_towers]
 * 매개변수: int num_disks - 초기화할 원반의 개수
 * 기능: 하노이 타워의 초기 상태를 설정
 */
void initialize_towers(int num_disks) {
    total_disks = num_disks;

    // 모든 타워 초기화
    for (int i = 0; i < 3; i++) {
        heights[i] = 0;
        for (int j = 0; j < MAX_DISKS; j++) {
            towers[i][j] = 0;
        }
    }

    // A 타워에 원반 쌓기 (크기가 큰 원반이 아래에 오도록)
    for (int i = num_disks; i >= 1; i--) {
        towers[0][heights[0]++] = i;
    }
}

/*
 * [함수: clear_screen]
 * 기능: 콘솔 화면을 지움 (운영체제별 다른 명령어 사용)
 */
void clear_screen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear"); // Unix/Linux/macOS
    #endif
}

/*
 * [함수: display_towers]
 * 기능: 하노이의 탑 현재 상태를 콘솔에 그래픽으로 표시
 */
void display_towers() {
    clear_screen();
    printf("\n===== 하노이 탑 시각화 (%d번째 이동) =====\n\n", move_count);

    // 원반 출력 (위에서부터 그림)
    for (int height = total_disks - 1; height >= 0; height--) {
        for (int tower = 0; tower < 3; tower++) {
            int disk_size = 0;

            // 해당 위치에 원반이 있는지 확인
            if (height < heights[tower]) {
                disk_size = towers[tower][height];
            }

            // 원반 그리기
            int spaces_before = (TOWER_WIDTH - disk_size) / 2;
            int spaces_after = TOWER_WIDTH - spaces_before - disk_size;

            printf("%*s", spaces_before, "");  // 왼쪽 공백

            if (disk_size > 0) {
                // 원반 표시 (크기에 따라 다른 수의 문자 사용)
                for (int i = 0; i < disk_size; i++) {
                    printf("%c", DISK_CHAR);
                }
            } else {
                // 원반이 없으면 막대만 표시
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

/*
 * [함수: move_disk]
 * 매개변수: 
 *   int from - 원반을 옮길 출발 기둥 (0=A, 1=B, 2=C)
 *   int to - 원반을 옮길 목적지 기둥 (0=A, 1=B, 2=C)
 * 기능: 한 기둥에서 다른 기둥으로 최상단 원반을 이동
 */
void move_disk(int from, int to) {
    if (heights[from] <= 0) {
        printf("오류: 기둥 %c에는 원반이 없습니다.\n", 'A' + from);
        return;
    }

    // 원반 이동
    int disk = towers[from][--heights[from]];  // 출발 기둥에서 원반 제거
    towers[to][heights[to]++] = disk;          // 도착 기둥에 원반 추가

    move_count++;
    display_towers();  // 이동 후 상태 표시

    // 원반 이동을 시각적으로 볼 수 있도록 잠시 대기
    usleep(500000);  // 0.5초 대기 (마이크로초 단위)
}

/*
 * [함수: hanoi_tower_visual]
 * 매개변수: 
 *   int n - 이동할 원반의 개수
 *   int from - 출발 기둥 (0=A, 1=B, 2=C)
 *   int via - 경유 기둥 (0=A, 1=B, 2=C)
 *   int to - 도착 기둥 (0=A, 1=B, 2=C)
 * 기능: 하노이 탑 이동 알고리즘의 재귀적 구현 (시각화 포함)
 */
void hanoi_tower_visual(int n, int from, int via, int to) {
    if (n == 1) {
        // 기저 조건: 원반이 1개면 바로 이동
        printf("원판 1: %c --> %c\n", 'A' + from, 'A' + to);
        move_disk(from, to);
    } else {
        // n-1개 원반을 출발 기둥에서 경유 기둥으로 이동
        hanoi_tower_visual(n - 1, from, to, via);
        
        // n번째(가장 큰) 원반을 출발 기둥에서 도착 기둥으로 이동
        printf("원판 %d: %c --> %c\n", n, 'A' + from, 'A' + to);
        move_disk(from, to);
        
        // n-1개 원반을 경유 기둥에서 도착 기둥으로 이동
        hanoi_tower_visual(n - 1, via, from, to);
    }
}

int main() {
    int num_disks;

    // 사용자로부터 원반 개수 입력 받기
    printf("원반의 개수를 입력하세요 (1-%d): ", MAX_DISKS);
    scanf("%d", &num_disks);

    // 입력 검증
    if (num_disks < 1 || num_disks > MAX_DISKS) {
        printf("원반 개수는 1에서 %d 사이여야 합니다.\n", MAX_DISKS);
        return 1;
    }

    // 타워 초기화 및 표시
    initialize_towers(num_disks);
    display_towers();  // 초기 상태 표시

    printf("하노이 탑 시작. 아무 키나 누르세요...\n");
    getchar();  // 입력 버퍼 비우기
    getchar();  // 사용자 입력 대기

    // 하노이 탑 알고리즘 실행 (A->C, B를 경유)
    hanoi_tower_visual(num_disks, 0, 1, 2);

    printf("\n하노이 탑 완성! 총 %d번 이동했습니다.\n", move_count);

    /*
     * [알고리즘 분석]
     * 원반 n개를 이동하는 데 필요한 최소 이동 횟수: 2^n - 1
     * 예: 3개 원반 -> 7번, 4개 원반 -> 15번, 5개 원반 -> 31번
     * 
     * [시간 복잡성]
     * 하노이 탑 알고리즘의 시간 복잡도는 O(2^n)으로, 원반 개수가 증가할수록
     * 필요한 이동 횟수가 기하급수적으로 증가합니다.
     * 이는 재귀 알고리즘의 특성 중 하나입니다.
     */

    return 0;
}
