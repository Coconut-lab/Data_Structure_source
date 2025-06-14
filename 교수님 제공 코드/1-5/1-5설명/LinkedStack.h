// 두근두근 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch05/LinkedStack.h

//-------------------------------------------------------------
// 코드 5.4 연결된 스택의 구현
//-------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 헤더 파일은 연결 리스트를 이용한 스택의 구현을 제공합니다.
 * 배열 기반 스택과 달리 크기 제한이 없고 동적으로 메모리를 할당하여 스택을 구현합니다.
 * 각 노드는 데이터와 다음 노드를 가리키는 포인터로 구성됩니다.
 */

// 연결된 스택 구조(Element는 이미 정의되어 있어야 하고, MAX_SIZE는 필요 없음)
typedef struct Node {   // 자기참조 구조체
    Element data;       // 데이터 필드(응용에 따라 다양하게 정의 가능)
    struct Node* link;  // 링크 필드(다음 노드를 가리키는 포인터)
} Node;
Node* top = NULL;       // 스택의 맨 위(top)를 가리키는 포인터

/*
 * [노드 할당 함수]
 * 새로운 노드를 동적으로 할당하고 초기화하는 함수
 * 매개변수: 노드에 저장할 데이터
 * 반환값: 할당된 노드의 포인터
 */
Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;    // 데이터 초기화
    p->link = NULL; // 링크 초기화
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
    Element e = p->data;    // 데이터 저장
    free(p);                // 노드 해제
    return e;               // 데이터 반환
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
 * [스택 기본 연산]
 * 스택이 비어있는지 확인(is_empty): top이 NULL이면 스택이 비어있음
 * 스택이 가득 찼는지 확인(is_full): 연결 리스트는 항상 확장 가능하므로 항상 0 반환
 * 스택 초기화(init_stack): top을 NULL로 설정
 */
int is_empty() { return top == NULL; }
int is_full() { return 0; }
void init_stack() { top = NULL; }

/*
 * [스택 삽입 함수]
 * 스택의 맨 위에 새로운 요소를 추가하는 함수
 * 매개변수: 추가할 데이터
 * 
 * [동작 과정]
 * 1. 새로운 노드 할당 및 데이터 저장
 * 2. 새 노드의 링크를 현재 top이 가리키는 노드로 설정
 * 3. top 포인터가 새 노드를 가리키도록 갱신
 */
void push(Element e)
{
    Node* p = alloc_node(e); // 그림 5.12의 (1)
    p->link = top;           // 그림 5.12의 (2)
    top = p;                 // 그림 5.12의 (3)
}

/*
 * [스택 삭제 함수]
 * 스택의 맨 위 요소를 제거하고 반환하는 함수
 * 반환값: 제거된 요소의 데이터
 * 
 * [동작 과정]
 * 1. 현재 top 노드의 포인터를 저장
 * 2. top 포인터를 다음 노드로 이동
 * 3. 이전 top 노드의 메모리를 해제하고 데이터 반환
 */
Element pop()
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = top;          // 그림 5.13의 (1)
    top = p->link;          // 그림 5.13의 (2)
    return free_node(p);    // 그림 5.13의 (3)
}

/*
 * [스택 조회(peek) 함수]
 * 스택의 맨 위 요소를 제거하지 않고 값만 반환하는 함수
 * 반환값: 맨 위 요소의 데이터
 */
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return top->data;
}

/*
 * [스택 메모리 해제 함수]
 * 스택의 모든 노드를 해제하는 함수
 * 스택이 비어있을 때까지 반복적으로 pop() 호출
 */
void destroy_stack()
{
    while (is_empty() == 0) pop();
}

//-------------------------------------------------------------
// 코드 5.6 연결된 스택의 size()함수
//-------------------------------------------------------------
/*
 * [스택 크기 계산 함수]
 * 스택에 저장된 요소의 수를 계산하는 함수
 * 반환값: 스택에 저장된 요소의 수
 * 
 * [동작 과정]
 * 1. 카운터 초기화
 * 2. top부터 시작하여 NULL을 만날 때까지 연결 리스트 순회
 * 3. 각 노드마다 카운터 증가
 */
int size()
{
    int count = 0;
    for (Node* p = top; p != NULL; p = p->link)
        count++;
    return count;
}
