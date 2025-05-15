// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch09/sort_all.c


//--------------------------------------------------------------------
// 코드 9.1 선택 정렬(제자리 정렬 방식)


#include <stdio.h>
#define SWAP(x,y,t)	((t)=(x),(x)=(y),(y)=(t))

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%3d", arr[i]);
    printf("\n");
}
void print_step(int arr[], int n, int val)
{
    printf("   Step%2d :", val);
    print_array(arr, n);
}

void selection_sort(int* A, int n)
{
	int tmp;							// SWAP()을 위한 임시변수
	for (int i = 0; i<n - 1; i++) {
		int least = i;					// 최소 요소의 인덱스
		for (int j = i + 1; j<n; j++)	// A[i+1~n-1]을 검사함 
			if (A[j]<A[least])			// 최소 요소보다 작으면
                least = j;				// 최소 요소 갱신
		SWAP(A[i], A[least], tmp);		// A[i]와 A[min] 교환 

        print_step(A, n, i+1);			// 대비문제 과정 출력용 문장
	}
}


//--------------------------------------------------------------------
// 코드 9.2 삽입 정렬

void insertion_sort(int A[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = A[i];                 // 미리 A[i]를 저장해 둠
        int j;
        for (j = i - 1; j >= 0; j--) {  // i-1부터 0까지 하나씩 줄이면서
            if (A[j] > key)             // A[j]가 더 크면
                A[j + 1] = A[j];        // A[j]를 뒤로 한 칸 이동
            else break;                 // 제 위치를 찾음. A[j]의 다음 위치
        }
        A[j + 1] = key;
        print_step(A, n, i);
    }
}


//--------------------------------------------------------------------
// 코드 9.3 버블 정렬

void bubble_sort(int A[], int n)
{
    int tmp;
    for (int end = n - 1; end > 0; end--) { // 정렬되지 않은 부분의 마지막 위치
        int bChanged = 0;
        for (int j = 0; j < end; j++)       // 한 번의 스캔: 0부터 end-1까지 진행
            if (A[j] > A[j + 1]) {          // 인접한 요소가 역전되어 있으면
                SWAP(A[j], A[j + 1], tmp);  // 교환
                bChanged = 1;               // 교환이 발생함
            }
        if (!bChanged) break;               // 교환이 한 번도 없었으면 종료
        print_step(A, n, n - end);
    }
}


//--------------------------------------------------------------------
// 코드 9.4 함수 포인터를 이용한 삽입 정렬

int ascend(int x, int y) { return y - x; }	// 오름차순 비교함수
int descend(int x, int y) { return x - y; }	// 내림차순 비교함수
void insertion_sort_fn(int A[], int n, int(*f)(int, int))
{
    for (int i = 1; i < n; i++) {
        int key = A[i];					// 미리 A[i]를 저장해 둠
        int j;
        for (j = i - 1; j >= 0; j--) {	// i-1부터 0까지 하나씩 줄이면서
            if (f(A[j], key) < 0) 		// A[j]가 더 크면
                A[j + 1] = A[j];		// A[j]를 뒤로 한 칸 이동
            else break;		            // 제자리를 찾음. A[j] 다음 위치.
        }
        A[j + 1] = key;					// A[i]는 j+1에 있어야 함. 제 위치에 복사
        print_step(A, n, i);			// 대비문제 과정 출력
    }
}


//--------------------------------------------------------------------
// 코드 9.6 병합 정렬

#define MAX_SIZE	1024
static void merge(int A[], int left, int mid, int right)
{
    static int sorted[MAX_SIZE];		// 병합된 리스트 저장을 위한 임시배열
							    // 분할 정렬된 list의 병합
    int i = left;       // 왼쪽 부분 배열 A[left~mid]의 시작 위치
    int j = mid+1;      // 오른쪽 부분 배열 A[mid+1~right]의 시작 위치
    int k = left;       // 임시 배열 B[left~right]의 시작 위치

    while (i <= mid && j <= right) {
        if (A[i] <= A[j])
            sorted[k++] = A[i++];
        else
            sorted[k++] = A[j++];
    }

    while (i <= mid  ) sorted[k++] = A[i++];	// 왼쪽에 남은 레코드 모두 복사
    while (j <= right) sorted[k++] = A[j++];	// 오른쪽에 남은 레코드 모두 복사

    for (i = left; i <= right; i++)		// 임시배열 B를 입력배열 A로 모두 복사
	    A[i] = sorted[i];
}

// 병합 정렬 알고리즘을 이용해 int 배열을 오름차순으로 정렬하는 함수
void merge_sort(int A[], int left, int right) {
    if (left<right) {
        int mid = (left + right) / 2;	// 리스트의 균등 분할
        merge_sort(A, left, mid);		// 부분 리스트 정렬
        merge_sort(A, mid + 1, right);	// 부분 리스트 정렬
        merge(A, left, mid, right);		// 병합
    }
}

//--------------------------------------------------------------------
// 코드 9.7 퀵 정렬

int partition(int A[], int left, int right)
{
    int pivot = A[left];                // 피벗
    int low = left + 1;                 // 왼쪽 배열을 위한 인덱스
    int high = right;                   // 오른쪽 배열을 위한 인덱스
    int tmp;
    while (low <= high) {
        while (low <= high && A[low] <= pivot) low++;
        while (low <= high && A[high] > pivot) high--;
        if (low < high)                 // 인덱스가 역전되지 않았으면
            SWAP(A[low], A[high], tmp); // 조건에 맞지 않는 두 요소 교환
    }
    SWAP(A[left], A[high], tmp);        // high와 피벗 교환
    return high;                        // 피벗의 인덱스 반환
}
void quick_sort(int A[], int left, int right)
{
    if (left < right) {                     // 요소가 2개 이상인 경우
        int q = partition(A, left, right);  // 피벗을 중심으로 좌우로 분할
        quick_sort(A, left, q - 1);         // 왼쪽 부분 정렬
        quick_sort(A, q + 1, right);        // 오른쪽 부분 정렬
    }
}

void printArray(int arr[], int n, char* str)
{
    printf("%s =", str);
    print_array(arr, n);
}


void main()
{
//	int 	list[9] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
    int 	list[9] = { 6, 3, 7, 4, 9, 1, 5, 2, 8 };

    printf(" Original =");
    print_array(list, 9);

 //    selection_sort(list, 7); 			    // 선택 정렬
	// printArray(list, 7, "Selection");	    // 결과 출력

	// insertion_sort(list, 4); 			    // 삽입 정렬
	// printArray(list, 4, "Insertion");

	// bubble_sort(list, 9); 			        // 버블 정렬
	// printArray(list, 9, "Bubble   ");

//	insertion_sort_fn(list, 7, descend); 	// 내림차순 선택정렬
//	printArray(list, 7, "Insert-De");

//	insertion_sort_fn(list, 7, ascend); 	// 오름차순 선택정렬
//	printArray(list, 7, "Insert-As");

//	shell_sort(list, 9); 	                // 셸 정렬
//	printArray(list, 9, "ShellSort");

	// merge_sort(list, 0, 8); 	// 내림차순 선택정렬 알고리즘
	// printArray(list, 9, "MergeSort");	// 정렬 후 배열 출력

//  quick_sort(list, 0, 6); 	// 내림차순 선택정렬 알고리즘
//  printArray(list, 7, "QuickSort");	// 정렬 후 배열 출력

}