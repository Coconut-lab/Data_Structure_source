// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch10/seq_search.c


//--------------------------------------------------------------------
// 코드 10.1 순차 탐색


#include <stdio.h>
int sequential_search(int A[], int key, int left, int right)
{
    for (int i = left; i <= right; i++)
        if (A[i] == key)    // 탐색에 성공하면
            return i;       // 인덱스 반환
    return -1;              // 탐색에 실패하면 -1 반환
}


//--------------------------------------------------------------------
// 코드 10.2 교환하기 전략이 추가된 순차 탐색

#define SWAP(x,y,t)	((t)=(x),(x)=(y),(y)=(t))

int sequential_search_transpose(int A[], int key, int left, int right)
{
    for (int i = left; i <= right; i++)
        if (A[i] == key) {          // 탐색에 성공하면
            if (i != left) {        // 맨 앞에 있는 요소가 아니면
                i -= 1;
                int tmp;
                SWAP(A[i], A[i + 1], tmp);
            }
            return i;
        }
    return -1;
}

void main()
{
    int	table[5] = { 35, 97, 41, 56, 28 };

    printf("순차 탐색 %d --> %d\n", 56, sequential_search(table, 56, 0, 4));
    printf("순차 탐색 %d --> %d\n", 62, sequential_search(table, 62, 0, 4));
    printf("순차탐색(교환) %d --> %d\n", 56, sequential_search_transpose(table, 56, 0, 4));
    printf("순차탐색(교환) %d --> %d\n", 56, sequential_search_transpose(table, 56, 0, 4));
}
