// 두근두근 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일: ch06/LinkedList.h

//--------------------------------------------------------------------
// 코드 6.4 연결된 단순 연결 리스트 구현
//--------------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 헤더 파일은 단순 연결 리스트(Singly Linked List)의 구현을 제공합니다.
 * 각 노드는 데이터와 다음 노드를 가리키는 포인터(링크)로 구성됩니다.
 * 리스트의 첫 번째 노드를 가리키는 head 포인터를 통해 전체 리스트에 접근합니다.
 */

// 리스트의 구조체(Element는 이미 정의되어 있어야 하고, MAX_SIZE는 필요 없음)
typedef struct Node {   // 자기참조 구조체
    Element data;       // 데이터 필드(응용에 따라 다양한 정의 가능)
    struct Node* link;  // 링크 필드 - 다음 노드를 가리키는 포인터
} Node;

Node* head = NULL;     // 리스트의 첫 번째 노드를 가리키는 포인터

/*
 * [노드 할당 함수]
 * 새로운 노드를 동적으로 할당하고 초기화하는 함수
 * 매개변수: 노드에 저장할 데이터
 * 반환값: 할당된 노드의 포인터
 */
Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;        // 데이터 초기화
    p->link = NULL;     // 링크 초기화
    return p;
}

/*
 * [노드 해제 함수]
 * 노드의 메모리를 해제하고 데이터를 반환하는 함수
 * 매개변수: 해제할 노드의 포인터
 * 반환값: 노드에 저장된 데이터
 */
Element free_node(Node* p)
{
    Element e = p->data;// 데이터 저장
    free(p);            // 노드 해제
    return e;           // 데이터 반환
}

/*
 * [에러 처리 함수]
 * 오류 메시지를 출력하고 프로그램을 종료하는 함수
 */
void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

/*
 * [리스트 기본 연산]
 * 리스트가 비어있는지 확인(is_empty): head가 NULL이면 리스트가 비어있음
 * 리스트가 가득 찼는지 확인(is_full): 연결 리스트는 항상 확장 가능하므로 항상 0 반환
 * 리스트 초기화(init_list): head를 NULL로 설정
 */
int is_empty() { return head == NULL; }
int is_full() { return 0; }
void init_list() { head = NULL; }

/*
 * [노드 탐색 함수]
 * 특정 위치의 노드 포인터를 반환하는 함수
 * 매개변수: 찾을 노드의 위치(인덱스)
 * 반환값: 해당 위치의 노드 포인터 또는 NULL(위치가 유효하지 않은 경우)
 * 
 * [동작 과정]
 * 1. pos가 음수면 NULL 반환
 * 2. head부터 시작하여 pos 위치까지 연결 리스트 순회
 * 3. 중간에 NULL을 만나면(리스트의 끝) NULL 반환
 * 4. pos 위치의 노드 포인터 반환
 */
Node* get_node(int pos)
{
    if (pos < 0) return NULL;
    Node* p = head;
    for (int i = 0; i < pos; i++, p = p->link)
        if (p == NULL) return NULL;
    return p;
}

/*
 * [데이터 조회 함수]
 * 특정 위치의 노드 데이터를 반환하는 함수
 * 매개변수: 조회할 노드의 위치(인덱스)
 * 반환값: 해당 위치의 노드 데이터
 */
Element get_entry(int pos)
{
    Node* p = get_node(pos);
    if (p == NULL)
        error("Invalid Position Error!");
    return p->data;
}

/*
 * [리스트 삽입 함수]
 * 지정된 위치에 새로운 노드를 삽입하는 함수
 * 매개변수: 삽입할 위치(인덱스), 삽입할 데이터
 * 
 * [동작 과정]
 * 1. 새 노드 할당 및 데이터 초기화
 * 2. 삽입 위치가 0(맨 앞)인 경우:
 *    - 새 노드의 링크를 현재 head로 설정
 *    - head를 새 노드로 업데이트
 * 3. 삽입 위치가 0이 아닌 경우:
 *    - 삽입 위치 바로 앞 노드 탐색
 *    - 위치가 유효하지 않으면 에러 처리
 *    - 새 노드의 링크를 앞 노드의 다음 노드로 설정
 *    - 앞 노드의 링크를 새 노드로 설정
 */
void insert(int pos, Element e)
{
    Node* p = alloc_node(e); // 데이터 노드 생성 및 초기화
    if (pos == 0) {          // 맨 앞에 삽입하는 경우
        p->link = head;
        head = p;
    }
    else {                    // 중간이나 끝에 삽입하는 경우
        Node* before = get_node(pos - 1);
        if (before == NULL)
            error("Invalid Position Error!");
        p->link = before->link;
        before->link = p;
    }
}

/*
 * [리스트 삭제 함수]
 * 지정된 위치의 노드를 삭제하고 데이터를 반환하는 함수
 * 매개변수: 삭제할 노드의 위치(인덱스)
 * 반환값: 삭제된 노드의 데이터
 * 
 * [동작 과정]
 * 1. 리스트가 비어있는지 확인
 * 2. 삭제할 노드 탐색
 * 3. 삭제할 노드의 바로 앞 노드 탐색
 * 4. 앞 노드가 NULL(삭제 위치가 0)이면 head를 다음 노드로 설정
 * 5. 그렇지 않으면, 앞 노드의 링크를 삭제할 노드의 다음 노드로 설정
 * 6. 삭제할 노드의 메모리 해제 및 데이터 반환
 */
Element delete(int pos)
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = get_node(pos);            // 삭제할 노드
    if (p == NULL)
        error("Invalid Position Error!");
    Node* before = get_node(pos - 1);   // 이전 노드
    if (before == NULL)                 // 첫 번째 노드 삭제
        head = head->link;
    else
        before->link = p->link;
    return free_node(p);
}

/*
 * [리스트 메모리 해제 함수]
 * 리스트의 모든 노드를 해제하는 함수
 * 리스트가 비어있을 때까지 반복적으로 첫 번째 노드 삭제
 */
void destroy_list()
{
    while (is_empty() == 0) delete(0);
}

/*
 * [리스트 크기 계산 함수]
 * 리스트에 저장된 노드의 수를 계산하는 함수
 * 반환값: 리스트에 저장된 노드의 수
 */
int size()
{
    int count = 0;
    for (Node* p = head; p != NULL; p = p->link) count++;
    return count;
}


//--------------------------------------------------------------------
// 코드 6.6 단순 연결리스트의 추가 연산
//--------------------------------------------------------------------

/*
 * [리스트 끝에 추가 함수]
 * 리스트의 맨 끝에 새로운 노드를 추가하는 함수
 * 매개변수: 추가할 데이터
 * 
 * 이미 구현된 insert 함수를 활용하여, 현재 리스트 크기 위치에 삽입
 */
void append(Element e)
{
    insert(size(), e);
}

/*
 * [리스트 끝에서 삭제 함수]
 * 리스트의 맨 끝 노드를 삭제하고 데이터를 반환하는 함수
 * 반환값: 삭제된 노드의 데이터
 * 
 * 이미 구현된 delete 함수를 활용하여, 마지막 위치의 노드를 삭제
 */
Element pop()
{
    return delete(size() - 1);
}

/*
 * [리스트 노드 값 교체 함수]
 * 지정된 위치의 노드 데이터를 새로운 값으로 교체하는 함수
 * 매개변수: 교체할 노드의 위치(인덱스), 새로운 데이터
 */
void replace(int pos, Element e)
{
    Node* p = get_node(pos);
    if (p == NULL)
        error("Invalid Position Error!");
    p->data = e;
}

/*
 * [리스트 데이터 검색 함수]
 * 지정된 데이터가 리스트에서 처음으로 나타나는 위치를 찾는 함수
 * 매개변수: 검색할 데이터
 * 반환값: 데이터가 있는 위치(인덱스) 또는 -1(데이터가 없는 경우)
 * 
 * [동작 과정]
 * 1. 인덱스와 포인터 초기화
 * 2. 리스트 처음부터 끝까지 순회하며 데이터 비교
 * 3. 일치하는 데이터를 찾으면 해당 인덱스 반환
 * 4. 끝까지 찾지 못하면 -1 반환
 */
int find(Element e)
{
    int i = 0;
    for (Node* p = head; p != NULL; p = p->link, i++)
        if (p->data == e) return i;
    return -1;
}
//--------------------------------------------------------------------
