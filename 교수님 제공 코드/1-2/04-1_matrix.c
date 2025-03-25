    // 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
    // 참고파일 ch02/04_matrix.c

    //-------------------------------------------------------------
    // 코드 2.4 행렬을 2차원 배열로 표현하기

    #include <stdio.h>
    #define ROWS 3
    #define COLS 3

    void print_mat(int m[ROWS][COLS], char* str, FILE*);
    void transpose_mat(int m[ROWS][COLS]);


    #include <stdlib.h>
    void main()
    {
        FILE* fp1;
        int mat[ROWS][COLS] = { 4, 0, 1, 1, 6, 5, 7, 3, 6 };

        fp1 = fopen("04-1_output.txt", "a+");

        print_mat(mat, "원래 행렬", fp1);
        transpose_mat(mat);
        print_mat(mat, "전치 행렬", fp1);

        fclose(fp1);
        system("open 04-1_output.txt");
    }

    void print_mat(int(* m)[COLS], char* str, FILE* fp1)
    {
        fprintf(stdout, "%s\n", str);   // 모니터 출력
        fprintf(fp1, "%s\n", str);   // 파일 출력
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                fprintf(stdout, " %3d", m[i][j]);
                fprintf(fp1, " %3d", m[i][j]);
            }
            fprintf(stdout, "\n");
            fprintf(fp1, "\n");
        }
    }

        void transpose_mat(int(* m)[COLS])
    {
        for (int i = 0; i < ROWS; i++) {
            for (int j = i+1; j < COLS; j++) {
                int tmp = m[i][j];
                m[i][j] = m[j][i];
                m[j][i] = tmp;
            }
        }
    }