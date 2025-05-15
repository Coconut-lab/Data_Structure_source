// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch06/DblLinkedDeque.h


//--------------------------------------------------------------------
// 코드 6.8 이중으로 연결된 덱의 구현(후단 삭제만)


// 덱의 데이터(Element는 미리 정의되어 있어야 함. MAX_SIZE는 필요 없음)
typedef struct DNode {
    Element data;       // 데이터
    struct DNode* prev; // 선행 노드
    struct DNode* next; // 후속 노드
} DNode;
DNode* front = NULL;    // 전단
DNode* rear = NULL;     // 후단

DNode* alloc_dnode(Element e)
{
    DNode* p = (DNode*)malloc(sizeof(DNode));
    p->data = e;	// 데이터 초기화
    p->prev = NULL;	// 선행노드 링크 초기화
    p->next = NULL;	// 후속노드 링크 초기화
    return p;
}
Element free_dnode(DNode* p)
{
    Element e = p->data;
    free(p);
    return e;
}
void error(char* str)
{
    printf("%s\n", str);
    exit(1);
};


// 연결된 덱의 주요 연산들
int is_empty() { return front == NULL; }
int is_full() { return 0; }
void init_deque() { front = rear = NULL; }
int size()
{
	int count = 0;
	for (DNode* p = front; p != NULL; p = p->next) count++;
	return count;
}
void add_front(Element e)
{
    DNode* p = alloc_dnode(e);
    if (is_empty())
        front = rear = p; 
    else {
	p->next = front;
	front->prev = p;
	front = p;
    }
}
void add_rear(Element e)
{
    DNode* p = alloc_dnode(e);
    if (is_empty())
	front = rear = p;
    else {
	p->prev = rear;
	rear->next = p;
	rear = p;
    }
}

// 전단 삭제 연산
Element delete_front()
{
    if (is_empty())
	error("Underflow Error!");

    DNode* p = front;			// 삭제할 노드
    if (front == rear)			// 요소가 하나인 경우
	front = rear = NULL;
    else {						// 요소가 둘 이상인 경우
	front = front->next;
	front->prev = NULL;
    }
    return free_dnode(p);
}

//--------------------------------------------------------------------
// 후단 삭제 연산
Element delete_rear()
{
    if (is_empty())
	error("Underflow Error!");

    DNode* p = rear;        // 그림 6.20의 (1)
    if (front == rear)      // 요소가 하나인 경우
        front = rear = NULL;
    else {                  // 요소가 둘 이상인 경우
        rear = rear->prev;  // 그림 6.20의 (2)
        rear->next = NULL;
    }
    return free_dnode(p);   // 그림 6.20의 (3)
}
//--------------------------------------------------------------------

// 탐색(peek) 연산
Element get_front()
{
    if (is_empty())
	error("Underflow Error!");
    return front->data;
}
Element get_rear()
{
    if (is_empty())
	error("Underflow Error!");
    return rear->data;
}

// 큐의 모든 요소 삭제(동적 해제)
void destroy_deque()
{
    while (is_empty() == 0)
	delete_rear();
}
