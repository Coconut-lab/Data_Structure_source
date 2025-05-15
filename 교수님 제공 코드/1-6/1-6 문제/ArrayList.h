// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch06/ArrayList.h


//--------------------------------------------------------------------
// 코드 6.1 배열 구조의 리스트


// 리스트의 데이터(Element와 MAX_SIZE는 미리 정의되어 있어야 함)
Element data[MAX_SIZE]; // 요소의 배열
int size = 0;           // 요소의 수
void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

// 리스트의 연산들
void init_list() { size = 0; }
int is_empty() { return size == 0; }
int is_full() { return size == MAX_SIZE; }

// 삽입 연산
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

// 삭제 연산
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

// 참조 연산
Element get_entry(int pos)
{
    if (is_empty())
        error("Underflow Error!");
    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");
    return data[pos];
}

//--------------------------------------------------------------------
// 코드 6.3 배열 구조의 리스트의 추가 연산

void append(Element e)
{
    insert(size, e);
}
Element pop()
{
    return delete(size - 1);
}
void replace(int pos, Element e)
{
    if (pos < 0 || pos >= size)
        error("Invalid Position Error!");
    data[pos] = e;
}
int find(Element e)
{
    for (int i = 0; i < size; i++)
        if (data[i] == e)
            return i;
    return -1;
}
//--------------------------------------------------------------------



