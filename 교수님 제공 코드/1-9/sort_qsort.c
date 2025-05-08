// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch09/sort_qsort.c


//--------------------------------------------------------------------
// 코드 9.7 퀵 정렬 라이브러리 함수 사용 예


#include <stdio.h>
#include <stdlib.h>

int compare(const void *arg1, const void *arg2)
{
    if (*(double *)arg1 > *(double *)arg2) return 1;
    else if (*(double *)arg1 < *(double *)arg2) return -1;
    else return 0;
}
void main()
{
    double list[9] = { 2.1, 0.9, 1.6, 3.8, 1.2, 4.4, 6.2, 9.1, 7.7 };

    printf("정렬 전: ");
    for (int i=0; i < 9; i++)
        printf("%4.1f ", list[i]);

    qsort((void *)list, 9, sizeof(double), compare);
    printf("\n정렬 후: ");
    for (int i=0; i<9; i++)
        printf("%4.1f ", list[i]);
    printf("\n");
}
