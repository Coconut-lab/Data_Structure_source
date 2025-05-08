// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일: ch06/LinkedList.h


//--------------------------------------------------------------------
// 코드 6.4 연결된 구조의 리스트 구현


// 리스트의 데이터(Element는 미리 정의되어 있어야 함하고, MAX_SIZE는 필요 없음)
typedef struct Node {   // 자기참조 구조체
    Element data;       // 데이터 필드(스택 요소)
    struct Node* link;  // 링크 필드
} Node;

Node* head = NULL;

// 단순 연결 구조 노드의 동적 할당 함수(코드 5.3과 동일)
Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;        // 데이터 초기화
    p->link = NULL;     // 링크 초기화
    return p;
}
// 단순 연결 구조 노드의 데이터 반환 및 동적 해제 함수(코드 5.3과 동일)
Element free_node(Node* p)
{
    Element e = p->data;// 데이터 복사
    free(p);            // 동적 해제
    return e;           // 데이터 반환
}

void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

// 리스트의 연산들
int is_empty() { return head == NULL; }
int is_full() { return 0; }
void init_list() { head = NULL; }
// 리스트 요소 접근 함수(노드, 데이터)
Node* get_node(int pos)
{
    if (pos < 0) return NULL;
    Node* p = head;
    for (int i = 0; i < pos; i++, p = p->link)
        if (p == NULL) return NULL;
    return p;
}
Element get_entry(int pos)
{
    Node* p = get_node(pos);
    if (p == NULL)
        error("Invalid Position Error!");
    return p->data;
}
// 리스트의 삽입 연산
void insert(int pos, Element e)
{
    Node* p = alloc_node(e); // 삽입할 노드 생성 및 초기화
    if (pos == 0) {
        p->link = head;
        head = p;
    }
    else {
        Node* before = get_node(pos - 1);
        if (before == NULL)
            error("Invalid Position Error!");
        p->link = before->link;
        before->link = p;
    }
}
// 리스트의 삭제 연산
Element delete(int pos)
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = get_node(pos);            // 삭제할 노드
    if (p == NULL)
        error("Invalid Position Error!");
    Node* before = get_node(pos - 1);   // 이전 노드
    if (before == NULL)                 // 맨 앞 노드 삭제
        head = head->link;
    else
        before->link = p->link;
    return free_node(p);
}
// 리스트의 모든 요소 삭제(동적 해제)
void destroy_list()
{
    while (is_empty() == 0) delete(0);
}
int size()
{
    int count = 0;
    for (Node* p = head; p != NULL; p = p->link) count++;
    return count;
}


//--------------------------------------------------------------------
// 코드 6.6 연결 리스트의 추가 연산

void append(Element e)
{
    insert(size(), e);
}
Element pop()
{
    return delete(size() - 1);
}
void replace(int pos, Element e)
{
    Node* p = get_node(pos);
    if (p == NULL)
        error("Invalid Position Error!");
    p->data = e;
}
int find(Element e)
{
    int i = 0;
    for (Node* p = head; p != NULL; p = p->link, i++)
        if (p->data == e) return i;
    return -1;
}
//--------------------------------------------------------------------
