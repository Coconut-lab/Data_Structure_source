// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch06/DblLinkedList.h


//--------------------------------------------------------------------
// 코드 6.7 이중 연결 리스트 구현


// 리스트의 데이터(Element는 미리 정의되어 있어야 함)
typedef struct DNode {
    Element data; // 데이터
    struct DNode* prev; // 선행 노드
    struct DNode* next; // 후속 노드
} DNode;

DNode org;

DNode* alloc_dnode(Element e) {
    DNode* p = (DNode*)malloc(sizeof(DNode));
    p->data = e; // 데이터 초기화
    p->prev = NULL; // 선행노드 링크 초기화
    p->next = NULL; // 후속노드 링크 초기화
    return p;
}
Element free_dnode(DNode* p) {
    Element e = p->data;
    free(p);
    return e;
}
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

// 리스트의 연산들
int is_empty() { return org.next == NULL; }
int is_full() { return 0; }
void init_list() { org.next = NULL; }

// 리스트 노드 및 데이터 접근
DNode* get_node(int pos) {
    DNode* p = &org;
    for (int i = 0; i <= pos; i++, p = p->next)
        if (p == NULL)
            return NULL;
    return p;
}

Element get_entry(int pos) {
    DNode* p = get_node(pos);
    if (pos < 0 || p == NULL)
        error("Invalid Position Error!");
    return p->data;
}
// 삽입 연산
void insert(int pos, Element e) {
    DNode* before = get_node(pos - 1);
    if (before == NULL)
        error("Invalid Position Error!");
    DNode* p = alloc_dnode(e);
    p->next = before->next;
    p->prev = before;
    before->next = p;
    if (p->next != NULL)
        p->next->prev = p;
}
// 삭제 연산
Element delete(int pos) {
    DNode* p = get_node(pos);
    if (pos < 0 || p == NULL)
        error("Invalid Position Error!");
    p->prev->next = p->next;
    if (p->next != NULL)
        p->next->prev = p->prev;
    return free_dnode(p);
}

void destroy_list() { while (is_empty() == 0) delete(0); }
int size() {
    int count = 0;
    for (DNode* p = org.next; p != NULL; p = p->next)
        count++;
    return count;
}


//--------------------------------------------------------------------
#ifdef XXX
// 리스트의 교체 연산
void replace(int pos, Element e) {
    DNode* p = get_node(pos);	// 삭제할 노드
    if (p == NULL)
        error("Invalid Position Error!");
    p->data = e;
}

// 리스트의 탐색 연산(순차 탐색)
int find(Element e) {
    int i = 0;
    for (DNode* p = head(); p != NULL; p = p->next, i++)
        if (p->data == e) return i;
    return -1;
}
#endif
