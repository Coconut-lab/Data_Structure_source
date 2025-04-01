#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep �Լ� ����� ���� ���

#define MAX_DISKS 8
#define TOWER_WIDTH 7
#define DISK_CHAR '*'

// 3���� ��� A, B, C�� ǥ���ϴ� �迭
int towers[3][MAX_DISKS];
int heights[3] = {0, 0, 0}; // �� ��տ� ���� ������ ����
int total_disks;
int move_count = 0;

// ���� �ʱ�ȭ �Լ�
void initialize_towers(int num_disks) {
    total_disks = num_disks;

    // ��� Ÿ�� �ʱ�ȭ
    for (int i = 0; i < 3; i++) {
        heights[i] = 0;
        for (int j = 0; j < MAX_DISKS; j++) {
            towers[i][j] = 0;
        }
    }

    // A Ÿ���� ���� �ױ� (ũ�Ⱑ ū ������ �Ʒ��� ������)
    for (int i = num_disks; i >= 1; i--) {
        towers[0][heights[0]++] = i;
    }
}

// ȭ�� ����� �Լ� (�ý��� ��ɾ� ���)
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ���� �ϳ��� ž ���� ��� �Լ�
void display_towers() {
    clear_screen();
    printf("\n===== �ϳ��� ž �ð�ȭ (%d��° �̵�) =====\n\n", move_count);

    // ���� ��� (���������� �׸���)
    for (int height = total_disks - 1; height >= 0; height--) {
        for (int tower = 0; tower < 3; tower++) {
            int disk_size = 0;

            // �ش� ��ġ�� ������ �ִ��� Ȯ��
            if (height < heights[tower]) {
                disk_size = towers[tower][height];
            }

            // ���� �׸���
            int spaces_before = (TOWER_WIDTH - disk_size) / 2;
            int spaces_after = TOWER_WIDTH - spaces_before - disk_size;

            printf("%*s", spaces_before, "");  // ���� ����

            if (disk_size > 0) {
                for (int i = 0; i < disk_size; i++) {
                    printf("%c", DISK_CHAR);
                }
            } else {
                // ������ ������ ��ո� ǥ��
                printf("|");
            }

            printf("%*s", spaces_after, "");  // ������ ����
            printf("   ");  // ��� ���� ����
        }
        printf("\n");
    }

    // ��� ��ħ�� �׸���
    for (int tower = 0; tower < 3; tower++) {
        for (int i = 0; i < TOWER_WIDTH; i++) {
            printf("=");
        }
        printf("   ");
    }
    printf("\n");

    // ��� �̸� ǥ��
    printf("   A      B      C   \n\n");
}

// ���� �̵� �Լ�
void move_disk(int from, int to) {
    if (heights[from] <= 0) {
        printf("����: ��� %c���� ������ �����ϴ�.\n", 'A' + from);
        return;
    }

    // ���� �̵�
    int disk = towers[from][--heights[from]];
    towers[to][heights[to]++] = disk;

    move_count++;
    display_towers();

    // ���� �̵��� �ð������� �� �� �ֵ��� ��� ����
    usleep(500000);  // 0.5�� ��� (����ũ���� ����)
}

// �ϳ��� ž �̵� �˰��� (�ð�ȭ ����)
void hanoi_tower_visual(int n, int from, int via, int to) {
    if (n == 1) {
        printf("���� 1: %c --> %c\n", 'A' + from, 'A' + to);
        move_disk(from, to);
    } else {
        hanoi_tower_visual(n - 1, from, to, via);
        printf("���� %d: %c --> %c\n", n, 'A' + from, 'A' + to);
        move_disk(from, to);
        hanoi_tower_visual(n - 1, via, from, to);
    }
}

int main() {
    int num_disks;

    printf("������ ������ �Է��ϼ��� (1-%d): ", MAX_DISKS);
    scanf("%d", &num_disks);

    if (num_disks < 1 || num_disks > MAX_DISKS) {
        printf("���� ������ 1���� %d ���̿��� �մϴ�.\n", MAX_DISKS);
        return 1;
    }

    initialize_towers(num_disks);
    display_towers();  // �ʱ� ���� ǥ��

    printf("�ϳ��� ž ����. �ƹ� Ű�� ��������...\n");
    getchar();  // �Է� ���� ����
    getchar();  // ����� �Է� ���

    // �ϳ��� ž �˰��� ���� (A->C, B�� ����)
    hanoi_tower_visual(num_disks, 0, 1, 2);

    printf("\n�ϳ��� ž �ϼ�! �� %d�� �̵��߽��ϴ�.\n", move_count);

    return 0;
}