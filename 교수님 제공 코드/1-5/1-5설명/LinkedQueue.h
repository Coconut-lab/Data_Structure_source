// 두근두근 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch05/LinkedQueue.h

/*
 * [프로그램 설명]
 * 이 헤더 파일은 연결 리스트를 이용한 큐의 구현을 제공합니다.
 * 배열 기반 큐와 달리 크기 제한이 없고 동적으로 메모리를 할당하여 큐를 구현합니다.
 * 각 노드는 데이터와 다음 노드를 가리키는 포인터로 구성됩니다.
 */

typedef struct Node {    // 자기참조 구조체
    Element data;        // 데이터 
    struct Node* link;   // 링크: 다음 노드를 가리킴 
} Node;
Node* front = NULL;      // 연결된 큐의 전단
Node* rear = NULL;       // 연결된 큐의 후단

/*
 * [노드 할당 함수]
 * 새로운 노드를 동적으로 할당하고 초기화하는 함수
 * 매개변수: 노드에 저장할 데이터
 * 반환값: 할당된 노드의 포인터
 */
Node* alloc_node(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;         // 데이터 초기화
    p->link = NULL;      // 링크 초기화
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
    free(p);                // 노드 메모리 해제
    return e;               // 저장된 데이터 반환
}

/*
 * [에러 처리 함수]
 * 오류 메시지를 출력하고 프로그램을 종료하는 함수
 */
void error(char* str)
{
    printf("%s\n", str);
    exit(1);
};

/*
 * [큐 기본 연산]
 * 큐가 비어있는지 확인(is_empty): front가 NULL이면 큐가 비어있음
 * 큐가 가득 찼는지 확인(is_full): 연결 리스트는 항상 확장 가능하므로 항상 0 반환
 * 큐 초기화(init_queue): front와 rear를 NULL로 설정
 */
int is_empty()    { return front == NULL; }
int is_full()     { return 0; }
void init_queue() { front = rear = NULL; }

/*
 * [큐 크기 계산 함수]
 * 큐에 저장된 요소의 수를 계산하는 함수
 * 반환값: 큐에 저장된 요소의 수
 * 
 * [동작 과정]
 * 1. 카운터 초기화
 * 2. front부터 시작하여 NULL을 만날 때까지 연결 리스트 순회
 * 3. 각 노드마다 카운터 증가
 */
int size()
{
    int count = 0;
    for (Node* p = front; p != NULL; p = p->link) count++;
    return count;
}

//-------------------------------------------------------------
// 코드 5.11 단순 연결(리스트) 큐의 삽입/삭제 연산
//-------------------------------------------------------------

/*
 * [큐 삽입 함수]
 * 큐의 후단(rear)에 새로운 요소를 추가하는 함수
 * 매개변수: 추가할 데이터
 * 
 * [동작 과정]
 * 1. 새로운 노드 할당 및 데이터 저장
 * 2. 큐가 비어있는 경우:
 *    - front와 rear 모두 새 노드를 가리키도록 설정
 * 3. 큐가 비어있지 않은 경우:
 *    - 현재 rear의 링크를 새 노드로 설정
 *    - rear 포인터를 새 노드로 업데이트
 */
void enqueue(Element e)
{
    Node* p = alloc_node(e);// 데이터 노드 생성
    if (is_empty())         // 현재 공백상태 큐이면
        front = rear = p;   // front와 rear가 p를 가리킴
    else {                  // 큐가 공백 상태가 아니면
        rear->link = p;     // p를 rear의 후속노드로 연결하고
        rear = p;           // rear를 이동(p를 가리키도록)
    }
}

/*
 * [큐 삭제 함수]
 * 큐의 전단(front)에서 요소를 제거하고 반환하는 함수
 * 반환값: 제거된 요소의 데이터
 * 
 * [동작 과정]
 * 1. 큐가 비어있는지 확인
 * 2. 현재 front 노드의 포인터를 저장
 * 3. front 포인터를 다음 노드로 이동
 * 4. 큐가 비어있게 되면 rear도 NULL로 설정
 * 5. 이전 front 노드의 메모리를 해제하고 데이터 반환
 */
Element dequeue()
{
    if (is_empty())
        error("Underflow Error!");
    Node* p = front;        // 제거할 노드를 가리키는 포인터
    front = front->link;    // front를 한 칸 전진
    if (front == NULL)      // 큐가 빈 상태가 되면,
        rear = NULL;        // rear도 NULL로 초기화
    return free_node(p);    // p의 메모리 해제하고 데이터 반환
}
//-------------------------------------------------------------

/*
 * [큐 탐색(peek) 함수]
 * 큐의 전단(front)의 데이터를 제거하지 않고 반환하는 함수
 * 반환값: 전단 요소의 데이터
 */
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return front->data;
}

/*
 * [큐 메모리 해제 함수]
 * 큐의 모든 노드를 해제하는 함수
 * 큐가 비어있을 때까지 반복적으로 dequeue() 호출
 */
void destroy_queue()
{
    while (is_empty() == 0)
        dequeue();
}
