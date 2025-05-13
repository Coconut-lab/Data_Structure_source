// 두근두근 자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch04/CircularQueue.h

//-------------------------------------------------------------
// 코드 4.1 배열을 이용한 원형 큐의 구현
//-------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 헤더 파일은 배열을 이용한 원형 큐의 기본 구현을 제공합니다.
 * 원형 큐는 선형 큐의 단점(메모리 낭비)을 해결하기 위해 배열의 처음과 끝이 연결된 형태로 구현됩니다.
 * 모듈로 연산(%)을 통해 원형 구조를 구현하여 데이터의 재활용이 가능합니다.
 */

// 원형 큐의 구조체(Element와 MAX_SIZE는 이미 정의되어 있어야 함)
Element data[MAX_SIZE]; // 데이터 배열
int front;              // 전단 인덱스 (데이터를 꺼내는 위치 바로 앞)
int rear;               // 후단 인덱스 (마지막으로 삽입된 데이터의 위치)

/*
 * [에러 처리 함수]
 * 오류 메시지를 출력하고 프로그램을 종료하는 함수
 * 매개변수: 출력할 오류 메시지
 */
void error(char* str)
{
    printf("%s\n", str);
    exit(1);
}

/*
 * [원형 큐 초기화 함수]
 * front와 rear를 모두 0으로 설정하여 큐를 초기화
 * 원형 큐에서는 front와 rear가 같으면 큐가 비어있는 상태
 */
void init_queue()
{
    front = rear = 0;
}

/*
 * [큐 공백 상태 확인 함수]
 * front와 rear가 같으면 큐가 비어있음
 * 반환값: 큐가 비어있으면 1, 그렇지 않으면 0
 */
int is_empty()
{
    return front == rear;
}

/*
 * [큐 포화 상태 확인 함수]
 * 원형 큐에서는 한 칸을 항상 비워두어 가득 찬 상태와 빈 상태를 구분
 * (rear+1)%MAX_SIZE가 front와 같으면 큐가 가득 찬 상태
 * 반환값: 큐가 가득 찼으면 1, 그렇지 않으면 0
 */
int is_full()
{
    return front == (rear + 1) % MAX_SIZE;
}

/*
 * [큐 삽입 함수]
 * 큐의 rear 위치에 새로운 데이터를 삽입
 * 매개변수: 삽입할 데이터
 * 
 * [동작 과정]
 * 1. 큐가 가득 찼는지 확인
 * 2. rear를 다음 위치로 이동(모듈로 연산 사용)
 * 3. 해당 위치에 데이터 저장
 */
void enqueue(Element val)
{
    if (is_full())
        error("Overflow Error!");
    rear = (rear + 1) % MAX_SIZE;
    data[rear] = val;
}

/*
 * [큐 삭제 함수]
 * 큐의 front 다음 위치에서 데이터를 제거하고 반환
 * 반환값: 제거된 데이터
 * 
 * [동작 과정]
 * 1. 큐가 비어있는지 확인
 * 2. front를 다음 위치로 이동(모듈로 연산 사용)
 * 3. 해당 위치의 데이터 반환
 */
Element dequeue()
{
    if (is_empty())
        error("Underflow Error!");
    front = (front + 1) % MAX_SIZE;
    return data[front];
}

/*
 * [큐 탐색(peek) 함수]
 * 큐에서 데이터를 제거하지 않고 front 다음 위치의 데이터만 반환
 * 반환값: front 다음 위치의 데이터
 */
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return data[(front + 1) % MAX_SIZE];
}

/*
 * [랜덤 전화번호 생성 함수]
 * 010-XXXX-XXXX 형식의 랜덤 전화번호를 생성
 * 매개변수: 생성된 전화번호를 저장할 문자열 포인터
 */
void generate_random_phone(char* phone) {
    int middle = rand() % 10000;
    int last = rand() % 10000;

    sprintf(phone, "010-%04d-%04d", middle, last);
}
