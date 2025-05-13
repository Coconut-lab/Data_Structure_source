// 두근두근 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch06/ArrayList.h

//--------------------------------------------------------------------
// 코드 6.1 배열 기반의 리스트
//--------------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 헤더 파일은 배열을 이용한 리스트(ArrayList)의 구현을 제공합니다.
 * 연속된 메모리 공간을 사용하여 데이터를 저장하고, 인덱스를 통해 요소에 직접 접근합니다.
 * 중간에 요소를 삽입하거나 삭제할 때는 데이터 이동이 필요합니다.
 */

// 리스트의 구조체(Element와 MAX_SIZE는 이미 정의되어 있어야 함)
Element data[MAX_SIZE]; // 데이터 배열
int size = 0;           // 저장된 수
/*
 * [에러 처리 함수]
 * 오류 메시지를 출력하고 프로그램을 종료하는 함수
 */
void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

/*
 * [리스트 기본 연산]
 * 리스트 초기화(init_list): 크기를 0으로 설정
 * 리스트가 비어있는지 확인(is_empty): 크기가 0이면 리스트가 비어있음
 * 리스트가 가득 찼는지 확인(is_full): 크기가 MAX_SIZE와 같으면 리스트가 가득 찼음
 */
void init_list() { size = 0; }
int is_empty() { return size == 0; }
int is_full() { return size == MAX_SIZE; }

/*
 * [리스트 삽입 함수]
 * 지정된 위치에 새로운 요소를 삽입하는 함수
 * 매개변수: 삽입할 위치(인덱스), 삽입할 데이터
 * 
 * [동작 과정]
 * 1. 리스트가 가득 찼는지 확인
 * 2. 삽입 위치가 유효한지 확인(0 <= pos <= size)
 * 3. 삽입 위치 이후의 모든 요소를 한 칸씩 뒤로 이동
 * 4. 지정된 위치에 데이터 저장
 * 5. 리스트 크기 증가
 */
void insert(int pos, Element e)
{
    if (is_full())
        error("Overflow Error!");

    if (pos < 0 || pos > size)
        error("Invalid Position Error!");

    for (int i = size - 1; i >= pos; i--)
        data[i + 1] = data[i];
    data[pos] = e;
    size += 1;
}

/*
 * [리스트 삭제 함수]
 * 지정된 위치의 요소를 삭제하고 반환하는 함수
 * 매개변수: 삭제할 요소의 위치(인덱스)
 * 반환값: 삭제된 요소의 데이터
 * 
 * [동작 과정]
 * 1. 리스트가 비어있는지 확인
 * 2. 삭제 위치가 유효한지 확인(0 <= pos < size)
 * 3. 삭제할 데이터 저장
 * 4. 삭제 위치 이후의 모든 요소를 한 칸씩 앞으로 이동
 * 5. 리스트 크기 감소
 * 6. 삭제된 데이터 반환
 */
Element delete(int pos)
{
    if (is_empty())
        error("Underflow Error!");

    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");

    Element e = data[pos];
    for (int i = pos + 1; i < size; i++)
        data[i - 1] = data[i];
    size -= 1;
    return e;
}

/*
 * [데이터 조회 함수]
 * 지정된 위치의 요소 데이터를 반환하는 함수
 * 매개변수: 조회할 요소의 위치(인덱스)
 * 반환값: 해당 위치의 요소 데이터
 */
Element get_entry(int pos)
{
    if (is_empty())
        error("Underflow Error!");
    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");
    return data[pos];
}

//--------------------------------------------------------------------
// 코드 6.3 배열 기반의 리스트의 추가 연산
//--------------------------------------------------------------------

/*
 * [리스트 끝에 추가 함수]
 * 리스트의 맨 끝에 새로운 요소를 추가하는 함수
 * 매개변수: 추가할 데이터
 * 
 * 이미 구현된 insert 함수를 활용하여, 현재 리스트 크기 위치에 삽입
 */
void append(Element e)
{
    insert(size, e);
}

/*
 * [리스트 끝에서 삭제 함수]
 * 리스트의 맨 끝 요소를 삭제하고 데이터를 반환하는 함수
 * 반환값: 삭제된 요소의 데이터
 * 
 * 이미 구현된 delete 함수를 활용하여, 마지막 위치의 요소를 삭제
 */
Element pop()
{
    return delete(size - 1);
}

/*
 * [리스트 요소 값 교체 함수]
 * 지정된 위치의 요소 데이터를 새로운 값으로 교체하는 함수
 * 매개변수: 교체할 요소의 위치(인덱스), 새로운 데이터
 */
void replace(int pos, Element e)
{
    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");
    data[pos] = e;
}

/*
 * [리스트 데이터 검색 함수]
 * 지정된 데이터가 리스트에서 처음으로 나타나는 위치를 찾는 함수
 * 매개변수: 검색할 데이터
 * 반환값: 데이터가 있는 위치(인덱스) 또는 -1(데이터가 없는 경우)
 * 
 * [동작 과정]
 * 1. 리스트 처음부터 끝까지 순차 검색
 * 2. 일치하는 데이터를 찾으면 해당 인덱스 반환
 * 3. 끝까지 찾지 못하면 -1 반환
 */
int find(Element e)
{
    for (int i = 0; i < size; i++)
        if (data[i] == e)
            return i;
    return -1;
}
//--------------------------------------------------------------------
