// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch05/CirLinkedQueue.h


//-------------------------------------------------------------
// 코드 5.8 연결된 큐의 구현


// 큐의 데이터(Element는 미리 정의되어 있어야 함. MAX_SIZE는 필요 없음)
typedef struct Node { // 자기참조 구조체
    Element data; // 데이터 필드(스택 요소)
    struct Node* link; // 링크 필드
} Node;
Node* rear = NULL;

Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e; // 데이터 초기화
    p->link = NULL; // 링크 초기화
    return p;
}
Element free_node(Node* p)
{
    Element e = p->data;    // 데이터 복사
    free(p);                // 동적 해제
    return e;               // 데이터 반환
}

void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

int is_empty() { return rear == NULL; }
int is_full() { return 0; }
void init_queue() { rear = NULL; }
// 삽입 연산
void enqueue(Element e)
{
    Node* p = alloc_node(e); // 그림 5.17의 (1)
    if (is_empty()) { // 공백 상태의 삽입
        rear = p;
        p->link = p;
    }
    else { // 공백이 아닐 때의 삽입
        p->link = rear->link; // 그림 5.17의 (2)
        rear->link = p; // 그림 5.17의 (3)
        rear = p; // 그림 5.17의 (4)
    }
}
// 삭제 연산
Element dequeue()
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = rear->link; // 그림 5.18의 (1)
    if (rear == p) // 노드가 하나인 경우
        rear = NULL;
    else // 노드가 둘 이상인 경우
        rear->link = p->link; // 그림 5.18의 (2)
    return free_node(p); // 그림 5.18의 (3)
}
// 탐색(peek) 연산
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return rear->link->data; // 전단 노드의 데이터 반환
}
// 모든 요소 삭제(동적 해제) 연산
void destroy_queue()
{
    while (is_empty() == 0) dequeue();
}


//-------------------------------------------------------------
// 코드 5.10 연결된 큐의 size() 연산

int size()
{
    if (is_empty()) // 공백인 경우는 0 반환
        return 0;
    int count = 1;
    for (Node* p = rear->link; p != rear; p = p->link)
        count++;
    return count;
}
