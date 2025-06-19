// HeapADT.h: 힙의 데이터와 연산(배열 구조)

// 주의: 응용에 따라 항상 다음을 먼저 정의해야 함
// #define HNode	...		// 트리 노드에 저장할 데이터 자료형
// #define MAX_HSIZE ...	// 힙트리 노드를 저장할 배열의 크기


// #define Compare(n1,n2)	((n1)->data - (n2)->data)

#define Parent(i) (heap[i/2])	// i의 부모 노드 
#define Left(i) (heap[i*2])		// i의 왼쪽 자식 노드 
#define Right(i) (heap[i*2+1])	// i의 오른쪽 자식 노드 


// 힙의 데이터 ----------------------------------------
HNode heap[MAX_HSIZE];
int heap_size=0;

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_heap()	{ heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap()	{ return (heap_size == MAX_HSIZE - 1); }

HNode heap_peek()		{ return heap[1]; }

void heap_push(HNode n)
{
	if (is_full_heap()) 
		error("Overflow Error!");
	
	heap_size += 1;				// 노드 하나 추가
	int i = heap_size;			// 추가된(마지막) 노드의 인덱스

	// 추가된 노드의 우선순위가 더 높으면 계속 업힙
	while (i != 1 && Compare(n, Parent(i)) > 0) {
		heap[i] = Parent(i);	// 부모를 끌어내림(복사)
		i /= 2;					// 한 레벨 올라감
	}
	heap[i] = n;				// 마지막 위치에 새 노드 복사
}

HNode heap_pop()
{
	if (is_empty_heap() != 0)
		error("Underflow Error!");

	HNode	root = heap[1];			// 힙의 루트 노드
	HNode	last = heap[heap_size];	// 힙의 마지막 노드
	int		pid = 1, cid = 2;		// 루트와 왼쪽 자식의 인덱스

	heap_size -= 1;					// 노드 하나 삭제

	while (cid <= heap_size) {
		// 오른쪽 자식의 우선순위가 더 높으면 cid는 오른쪽 자식의 인덱스
		if (cid<heap_size && Compare(Left(pid), Right(pid))<0)
			cid++;

		// 마지막 노드의 우선순위가 자식보다 높으면 --> 제자리를 찾음
		if (Compare(last, heap[cid]) >= 0)
			break;

		// 아니면
		heap[pid] = heap[cid];		// 자식을 부모로 끌어올림
		pid = cid;					// 한 레벨 내려감
		cid *= 2;					// 한 레벨 내려감
	}
	heap[pid] = last;

	return root;
}
