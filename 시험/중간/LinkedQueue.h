// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch05/LinkedQueue.h


typedef struct Node {	// 데이터는 노드에 저장되어 관리됨
    Element data;	// 데이터 
    struct Node* link;	// 링크: 다음 노드를 가리킴 
} Node;
Node* front = NULL;	// 연결된 큐의 전단
Node* rear = NULL;	// 연결된 큐의 후단

// 단순 연결 구조 노드의 동적 할당과 해제 함수
Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;	    // 데이터 초기화
    p->link = NULL;	    // 링크 초기화
    return p;
}
Element free_node(Node* p)
{
    Element e = p->data;    // 데이터 복사
    free(p);                // 노드 동적 해제
    return e;               // 노드의 데이터 반환
}
void error(char* str)
{
    printf("%s\n", str);
    exit(1);
};

int is_empty()		{ return front == NULL; }
int is_full()		{ return 0; }
void init_queue()	{ front = rear = NULL; }
int size()
{
    int count = 0;
    for (Node* p = front; p != NULL; p = p->link) count++;
    return count;
}

//-------------------------------------------------------------
// 코드 5.11 단순 연결(비원형) 큐의 삽입/삭제 연산

void enqueue(Element e)
{
    Node* p = alloc_node(e);// 삽입할 노드 생성
    if (is_empty())         // 공백 상태의 삽입이면
        front = rear = p;   // front와 rear가 p를 가리킴
    else {                  // 큐가 공백 상태가 아니면
        rear->link = p;     // p를 rear의 후속노드로 연결하고
        rear = p;           // rear를 이동(p를 가리키도록)
    }
}
Element dequeue()
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = front;        // 삭제할 노드를 가리키는 포인터
    front = front->link;    // front는 한 칸 전진
    if (front == NULL)      // 삭제 후 공백 상태가 되면,
        rear = NULL;        // rear도 NULL로 초기화
    return free_node(p);    // p를 동적 해제하고 데이터 반환
}
//-------------------------------------------------------------

// 큐의 탐색(peek) 연산
Element peek()
{
    if (is_empty())
	error("Underflow Error!");
    return front->data;
}

// 큐의 모든 요소 삭제(동적 해제)
void destroy_queue()
{
    while (is_empty() == 0)
	dequeue();
}
