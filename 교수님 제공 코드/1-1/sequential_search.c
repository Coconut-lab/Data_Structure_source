// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch01/sequential_search.c

#include <stdio.h>


//-------------------------------------------------------------
// 코드 1.3 순차 탐색

int sequential_search(int A[], int n, int key)
{
    for (int i = 0; i<n; i++)
	if (A[i] == key)
	    return i;		// 탐색이 성공하면 인덱스 반환 
    return -1;			// 탐색이 실패하면 -1 반환
}

//-------------------------------------------------------------
// 테스트 프로그램
void main()
{
	int arr[10] = { 5, 9, 10, 17, 21, 29, 33, 37, 38, 43 };
	int index;

	index = sequential_search(arr, 10, 5);
	printf(" 5의 위치 = %d\n", index);
	index = sequential_search(arr, 10, 43);
	printf("43의 위치 = %d\n", index);
	index = sequential_search(arr, 10, 42);
	printf("42의 위치 = %d\n", index);

}