#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 3

int main(void) {
    int ary[MAX];
    int* p = ary;
    int stop;

    ary[0] = 7;
    ary[1] = 1;
    ary[MAX - 1] = 9;

    printf("%d\n", ary[0]); // 7, 직접접근

    printf("%d\n", p[0]); // 7, 간접접근
    printf("%d\n", p[1]); // 1, 간접접근
    printf("%d\n", p[MAX - 1]); // 9, 간접접근

    for (int i = 0; i < MAX; i++) {
        printf("%d\n", p[i]);
    }

    scanf("%d", &stop);
    
    return 0;
}