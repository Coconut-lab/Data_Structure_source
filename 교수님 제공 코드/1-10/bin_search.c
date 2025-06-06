// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch10/bin_search.c

#include <stdio.h>


//--------------------------------------------------------------------
// 코드 10.3 이진 탐색(순환 구조)


int binary_search(int A[], int key, int low, int high)
{
    if (low <= high) {              // 탐색할 레코드가 있으면
        int mid = (low + high) / 2; // 중앙 인덱스 계산
        printf("->%d", A[mid]);
        if (key == A[mid])          // 탐색 성공
            return mid;
        else if (key < A[mid])      // 왼쪽(left~middle-1)만 다시 탐색
            return binary_search(A, key, low, mid - 1);
        else                        // 오른쪽(middle+1~right)만 다시 탐색
            return binary_search(A, key, mid + 1, high);
    }
    return -1;                      // 탐색 실패
}


//--------------------------------------------------------------------
// 코드 10.4 이진 탐색(반복 구조)


int binary_search_iter(int A[], int key, int low, int high)
{
    while (low <= high) {           // 탐색할 레코드가 있으면
        printf(".");
        int mid = (low + high) / 2; // 중앙 인덱스 계산
        if (key == A[mid])          // 탐색 성공
            return mid;
        else if (key < A[mid])      // 왼쪽(left~middle-1)만 다시 탐색
            high = mid - 1;
        else                        // 오른쪽(middle+1~right)만 다시 탐색
            low = mid + 1;          // mid+1 ~ high 사이 검색
    }
    return -1;                      // 탐색 실패
}


//--------------------------------------------------------------------
// 보간 탐색


int binary_search_interpolation(int A[], int key, int low, int high)
{
    if (low <= high) {				// 하나 이상의 항목이 있어야 탐색
	int mid = (int)((float)(key - A[low]) /
		(A[high] - A[low]) * (high - low)) + low;
        printf("->%d", A[mid]);

	if (key == A[mid])			// 탐색 성공
	    return mid;
	else if (key < A[mid])		// 왼쪽 부분리스트 탐색 
	    return binary_search_interpolation(A, key, low, mid - 1);
	else						// 오른쪽 부분리스트 탐색 
	    return binary_search_interpolation(A, key, mid + 1, high);
    }
    return -1;        				// 탐색 실패
}

void main()
{
    int	list[16] = { 8, 11, 12, 15, 16, 19, 20, 23, 25, 28, 29, 31, 33, 35, 38, 40 };
    int key = 28;
    printf("  %d 이진탐색(순환): %d\n", key, binary_search(list, key, 0, 15));
    printf("  %d 이진탐색(보간): %d\n", key, binary_search_interpolation(list, key, 0, 15));
    printf("\n");
}


