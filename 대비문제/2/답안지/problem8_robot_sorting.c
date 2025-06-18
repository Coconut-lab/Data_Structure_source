// ���� 8: �κ� ��ġ ���� ���� (����ȭ ����)
// RobotPosition.h�� ����� �κ� ��ġ ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RobotPosition.h"

// ���� ���ؿ� ���� �� �Լ���

// 1. �������κ����� �Ÿ��� ��
int compare_by_distance(const void* a, const void* b) {
    RobotPosition* robot_a = (RobotPosition*)a;
    RobotPosition* robot_b = (RobotPosition*)b;
    
    double dist_a = calculate_distance(*robot_a);
    double dist_b = calculate_distance(*robot_b);
    
    if (dist_a < dist_b) return -1;
    else if (dist_a > dist_b) return 1;
    else return robot_a->robot_id - robot_b->robot_id;
}

// 2. X��ǥ �켱, Y��ǥ ���� ��
int compare_by_x_then_y(const void* a, const void* b) {
    RobotPosition* robot_a = (RobotPosition*)a;
    RobotPosition* robot_b = (RobotPosition*)b;
    
    if (robot_a->x != robot_b->x) {
        return robot_a->x - robot_b->x;
    }
    return robot_a->y - robot_b->y;
}

// 3. Y��ǥ �켱, X��ǥ ���� ��  
int compare_by_y_then_x(const void* a, const void* b) {
    RobotPosition* robot_a = (RobotPosition*)a;
    RobotPosition* robot_b = (RobotPosition*)b;
    
    if (robot_a->y != robot_b->y) {
        return robot_a->y - robot_b->y;
    }
    return robot_a->x - robot_b->x;
}

// sort_all.c ������ Ȱ���� ���� ���� (�Ÿ� ����)
void selection_sort_by_distance(RobotPosition robots[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        double min_dist = calculate_distance(robots[i]);
        
        for (int j = i + 1; j < count; j++) {
            double curr_dist = calculate_distance(robots[j]);
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            swap_robots(&robots[i], &robots[min_idx]);
        }
    }
}

// qsort ���̺귯�� �Լ��� �̿��� ����
void library_sort_robots(RobotPosition robots[], int count, SortCriteria criteria) {
    switch (criteria) {
        case SORT_BY_DISTANCE:
            qsort(robots, count, sizeof(RobotPosition), compare_by_distance);
            break;
        case SORT_BY_X_THEN_Y:
            qsort(robots, count, sizeof(RobotPosition), compare_by_x_then_y);
            break;
        case SORT_BY_Y_THEN_X:
            qsort(robots, count, sizeof(RobotPosition), compare_by_y_then_x);
            break;
        default:
            break;
    }
}

// ������ �׽�Ʈ �Լ�
void test_robot_sorting() {
    // ���� �κ� ��ġ ����
    RobotPosition robots[8];
    RobotPosition backup[8];
    int count = 8;
    
    generate_random_positions(robots, count);
    memcpy(backup, robots, sizeof(RobotPosition) * count);
    
    // ���� ���
    print_robots(robots, count, "���� ��");
    
    // �Ÿ��� ����
    memcpy(robots, backup, sizeof(RobotPosition) * count);
    library_sort_robots(robots, count, SORT_BY_DISTANCE);
    print_robots(robots, count, "�Ÿ��� ����");
    
    // X��ǥ �켱 ����
    memcpy(robots, backup, sizeof(RobotPosition) * count);
    library_sort_robots(robots, count, SORT_BY_X_THEN_Y);
    print_robots(robots, count, "X��ǥ �켱 ����");
    
    // Y��ǥ �켱 ����
    memcpy(robots, backup, sizeof(RobotPosition) * count);
    library_sort_robots(robots, count, SORT_BY_Y_THEN_X);
    print_robots(robots, count, "Y��ǥ �켱 ����");
}

int main() {
    test_robot_sorting();
    return 0;
}
