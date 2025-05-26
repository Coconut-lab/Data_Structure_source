// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch07/MaxHeap.c


//--------------------------------------------------------------------
// 코드 7.10 최대 힙의 연산과 테스트 프로그램


#include <stdio.h>
#include <stdlib.h>

#define MAX_HSIZE 100   // 힙을 위한 배열의 크기
#define PARENT(i) (i/2) // i의 부모 인덱스
#define LEFT(i) (i*2)   // i의 왼쪽 자식 인덱스
#define RIGHT(i) (i*2+1)// i의 오른쪽 자식 인덱스

typedef int HNode;      // 힙에 저장할 데이터의 자료형
HNode A[MAX_HSIZE];     // 힙을 저장하는 배열
int heap_size = 0;      // 힙의 전체 노드 수
#define KEY(i) (A[i])   // i의 킷값

void init_heap() { heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap() { return (heap_size == MAX_HSIZE - 1); }
HNode heap_peek() { return A[1]; }

void heap_push(HNode n)
{
    if (is_full_heap())         // 힙이 포화 상태
        return;
    heap_size += 1;             // 노드 하나 추가
    A[heap_size] = n;           // 말단 위치에 노드 삽입
    int i = heap_size;          // 말단 위치에서 업 힙 시작
    while (i != 1) {
        if (KEY(i) > KEY(PARENT(i))) {
            A[i] = A[PARENT(i)];// i와 부모를 교환
            A[PARENT(i)] = n;
            i = PARENT(i);      // 한 레벨 올라감
        }
        else break;             // 제자리 찾음
    }
}
HNode heap_pop()
{
    if (is_empty_heap())        // 힙이 공백 상태
        return -1;
    HNode root = A[1];          // 힙의 루트 노드
    HNode last = A[heap_size];  // 힙의 말단 노드
    A[1] = last;                // 말단 노드를 일단 루트에 복사
    heap_size -= 1;             // 노드 하나 삭제
    int i = 1;                  // 루트에서 다운 힙 시작

    while (LEFT(i) <= heap_size) {
        int child = (LEFT(i) < heap_size && KEY(LEFT(i)) > KEY(RIGHT(i)))
            ? LEFT(i) : RIGHT(i);
        if (KEY(i) > KEY(child)) break; // 제 자리를 찾았음
        A[i] = A[child];                // i와 더 큰 자식 교환
        A[child] = last;
        i = child;                      // 한 레벨 내려감
    }
    return root;
}
// 힙 트리 출력 함수.
void print_heap()
{
    for (int i = 1; i <= heap_size; i++)
        printf("%2d", A[i]);
    printf("\n");
}

//--------------------------------------------------------------------
// 코드 7.11 배열이 최대 힙인지 검사하기

int is_max_heap(HNode arr[], int len)
{
    for (int i = 1; i <= len / 2; i++)
        if (arr[i] < arr[LEFT(i)] || arr[i] < arr[RIGHT(i)])
            return 0;   // 크기 조건이 맞지 않음 -> 최대 힙이 아님
    return 1;           // 모든 노드에서 크기 조건 만족 -> 최대힙 맞음
}
//--------------------------------------------------------------------

// 테스트 프로그램
void main()
{
    int data[] = { 2, 5, 4, 8, 9, 3, 7, 3 };
    init_heap();
 
    printf("\n최대 힙 삭제 연산 테스트\n");
    for (int i = 0; i < 8; i++) {
        heap_push(data[i]);
        printf("%2d ---> ", data[i]);
        print_heap();
    }
    printf("\n최대 힙 삭제 연산 테스트\n");
    while (!is_empty_heap()) {
        printf("%2d <--- ", heap_pop());
        print_heap();
    }
    printf("\n");


    // 코드 7.11 테스트
    int a[] = { 0, 9, 7, 6, 5, 4, 3, 2, 2, 1, 3 }; // 최대힙 맞음
    int b[] = { 0, 9, 7, 6, 5, 3, 3, 2, 2, 1, 4 }; // 최대힙 맞음
    printf("a[]: 최대힙 %s\n", is_max_heap(a, 11) ? "맞음" : "아님");
    printf("b[]: 최대힙 %s\n", is_max_heap(b, 11) ? "맞음" : "아님");
}


#ifdef XXX
#include <stdio.h>
#include <stdlib.h>

#define MAX_HSIZE 100	// 힙트리 노드를 저장할 배열의 크기
#define PARENT(i) (i/2)	    // i의 부모 인덱스
#define LEFT(i)   (i*2)		// i의 왼쪽 자식 인덱스
#define RIGHT(i)  (i*2+1)	// i의 오른쪽 자식 인덱스

// 힙의 데이터 ----------------------------------------
typedef int HNode;		// HNode의 자료형 정의
HNode A[MAX_HSIZE];     // 힙을 저장하는 배열
int heap_size = 0;      // 힙의 전체 노드 수

#define KEY(i)  (A[i])	// 인덱스 i의 킷값

void init_heap()    { heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap()  { return (heap_size == MAX_HSIZE - 1); }
HNode heap_peek()   { return A[1]; }


void heap_push(HNode n)
{
    if (is_full_heap())             // 힙이 가득 찬 상태
        return;

    heap_size += 1;				    // 노드 하나 추가
    int i = heap_size;			    // 추가된(마지막) 노드의 인덱스
    A[i] = n;				        // 말단 위치에 노드 삽입

    while (i != 1) {
        if (KEY(i) > KEY(PARENT(i))) {
            A[i] = A[PARENT(i)];	// i와 부모를 교환
            A[PARENT(i)] = n;
            i = PARENT(i);			// 한 레벨 올라감
        }
        else break;                 // 제자리 찾음
    }
}

HNode heap_pop()
{
    if (is_empty_heap())            // 힙이 공백 상태
        return -1;

    HNode	root = A[1];			// 힙의 루트 노드
    HNode	last = A[heap_size];	// 힙의 말단 노드
    A[1] = last;	                // 말단 노드를 일단 루트에 복사
    heap_size -= 1;					// 노드 하나 삭제
    int		i = 1;		            // 루트에서 다운힙 시작

    while (LEFT(i) <= heap_size) {
        int child = (LEFT(i) < heap_size && KEY(LEFT(i)) > KEY(RIGHT(i)))
                    ? LEFT(i) : RIGHT(i);

        if (KEY(i) > KEY(child)) break; // 제 자리를 찾았음
        A[i] = A[child];		    // i와 더 큰 자식 교환
        A[child] = last;
        i = child;					// 한 레벨 내려감
    }
    return root;
}

void print_heap()
{
    for (int i = 1; i <= heap_size; i++)
        printf("%2d", A[i]);
    printf("\n");
}

int is_max_heap(HNode arr[], int len)
{
    for (int i = 1; i <= len / 2; i++)
        if (arr[i] < arr[LEFT(i)] || arr[i] < arr[RIGHT(i)])
            return 0;   // 크기 조건이 맞지 않음 -> 최대 힙이 아님
    return 1;           // 모든 노드에서 크기 조건 만족 -> 최대힙 맞음
}



void main()
{
	int data[] = { 2, 5, 4, 8, 9, 3, 7, 3 };
    init_heap();

    printf("최대 힙 삽입 연산 테스트\n");
    for (int i = 0; i < 8; i++) {
		heap_push(data[i]);
		printf("%2d ---> ", data[i]);
		print_heap();
	}
    printf("\n최대 힙 삭제 연산 테스트\n");
	while (!is_empty_heap()) {
		printf("%2d <--- ", heap_pop());
		print_heap();
	}

    int a[] = { 0, 9, 7, 6, 5, 4, 3, 2, 2, 1, 3 };	// 검사 성공: 최대힙 맞음
    int b[] = { 0, 9, 7, 6, 5, 3, 3, 2, 2, 1, 4 };	// 검사 성공: 최대힙 맞음
    printf("a[]: 최대힙 %s\n", is_max_heap(a, 11) ? "맞음" : "아님");
    printf("b[]: 최대힙 %s\n", is_max_heap(b, 11) ? "맞음" : "아님");
}
#endif
