// ���� ���� C�ڷᱸ��(�ֿ���, ���� ���ǻ�, 2024)
// ��������: ch03/HanoiTower.c

//-------------------------------------------------------------
// �ڵ� 3.10 �ϳ����� ž
#include <stdio.h>
void hanoi_tower(int n, char from, char tmp, char to)
{
    if (n == 1)
        printf("���� 1: %c --> %c\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        printf("���� %d: %c --> %c\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
}

void main() {
    hanoi_tower(3, 'A', 'B', 'C');
}
