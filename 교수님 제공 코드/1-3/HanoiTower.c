// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일: ch03/HanoiTower.c

//-------------------------------------------------------------
// 코드 3.10 하노이의 탑
#include <stdio.h>
void hanoi_tower(int n, char from, char tmp, char to)
{
    if (n == 1)
        printf("원판 1: %c --> %c\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        printf("원판 %d: %c --> %c\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
}

void main() {
    hanoi_tower(3, 'A', 'B', 'C');
}
