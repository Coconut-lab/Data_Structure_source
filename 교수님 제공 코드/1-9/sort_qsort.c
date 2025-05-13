// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch09/sort_qsort.c


//--------------------------------------------------------------------
// 코드 9.7 퀵 정렬 라이브러리 함수 사용 예


#include <stdio.h>
#include <stdlib.h>

int compare(const void *arg1, const void *arg2)
{
    if (*(double *)arg1 > *(double *)arg2) return 1; // arg1이 더 크면 1
    else if (*(double *)arg1 < *(double *)arg2) return -1; // arg2가 더 크면 -1
    else return 0;  // 같으면 0
}
void main()
{
    double list[9] = { 2.1, 0.9, 1.6, 3.8, 1.2, 4.4, 6.2, 9.1, 7.7 };

    printf("정렬 전: ");
    for (int i=0; i < 9; i++)
        printf("%4.1f ", list[i]);

    // 첫번째 인자 => DB, 두번째 인자 => 갯수, 세번째 인자 => 크기 네번째 인자 => 함수의 주소
    qsort((void *)list, 9, sizeof(double), compare); // stdlib.h의 qsort() 함수 사용, 라이브러리 사용
    printf("\n정렬 후: ");
    for (int i=0; i<9; i++)
        printf("%4.1f ", list[i]);
    printf("\n");
}
