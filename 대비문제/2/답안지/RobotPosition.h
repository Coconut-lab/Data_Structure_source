// 로봇 위치 정렬을 위한 헤더 파일
// RobotPosition.h (sort_all.c와 TreeLinked.h를 참고하여 제작)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ROBOTS 100
#define FIELD_SIZE 100

// 로봇의 2D 위치를 나타내는 구조체
typedef struct {
    int x;           // X 좌표
    int y;           // Y 좌표
    int robot_id;    // 로봇 ID
} RobotPosition;

// 정렬 기준 열거형
typedef enum {
    SORT_BY_DISTANCE,    // 원점으로부터의 거리순
    SORT_BY_X_THEN_Y,    // X좌표 우선, Y좌표 차순
    SORT_BY_Y_THEN_X,    // Y좌표 우선, X좌표 차순
    SORT_BY_ANGLE        // 원점에서의 각도순
} SortCriteria;

// 랜덤 로봇 위치 생성
void generate_random_positions(RobotPosition robots[], int count) {
    srand(time(NULL));
    
    for (int i = 0; i < count; i++) {
        robots[i].x = rand() % FIELD_SIZE - FIELD_SIZE/2;  // -50 ~ 49
        robots[i].y = rand() % FIELD_SIZE - FIELD_SIZE/2;  // -50 ~ 49
        robots[i].robot_id = i + 1;
    }
}

// 원점으로부터의 거리 계산
double calculate_distance(RobotPosition robot) {
    return sqrt(robot.x * robot.x + robot.y * robot.y);
}

// 원점에서의 각도 계산 (라디안)
double calculate_angle(RobotPosition robot) {
    return atan2(robot.y, robot.x);
}

// 로봇 위치 출력
void print_robot(RobotPosition robot) {
    printf("Robot%2d: (%3d, %3d)", robot.robot_id, robot.x, robot.y);
}

// 로봇 배열 출력
void print_robots(RobotPosition robots[], int count, char* title) {
    printf("%s:\n", title);
    for (int i = 0; i < count; i++) {
        printf("  ");
        print_robot(robots[i]);
        if (i % 3 == 2) printf("\n");  // 3개씩 한 줄에 출력
        else printf("  ");
    }
    if (count % 3 != 0) printf("\n");
    printf("\n");
}

// 두 로봇 위치 교환 (sort_all.c의 SWAP 매크로 참고)
void swap_robots(RobotPosition* a, RobotPosition* b) {
    RobotPosition temp = *a;
    *a = *b;
    *b = temp;
}
