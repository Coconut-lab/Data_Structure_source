// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch02/matrix.c

//-------------------------------------------------------------
// 코드 2.4 행렬을 2차원 배열로 표현하기

#include <stdio.h>
#define ROWS 3
#define COLS 3

void print_mat(int m[ROWS][COLS], char* str)
{
    printf("%s\n", str);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(" %3d", m[i][j]);
        }
        printf("\n");
    }
}
void transpose_mat(int m[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = i+1; j < COLS; j++) {
            int tmp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = tmp;
        }
    }
}

#include <stdlib.h>
void main()
{
    int mat[ROWS][COLS] = { 4, 0, 1, 1, 6, 5, 7, 3, 6 };
    print_mat(mat, "원래 행렬");
    transpose_mat(mat);
    print_mat(mat, "전치 행렬");
}
