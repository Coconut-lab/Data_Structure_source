// 두근두근 자료구조 개정판(최영규, 생능 출판사)
// 참고파일 ch03/ArrayStack.h

//-------------------------------------------------------------
// 코드 3.1 배열을 이용한 스택의 구현


// 스택의 데이터(Element와 MAX_SIZE는 미리 정의되어 있어야 함)
Element data[MAX_SIZE]; // 스택 요소의 배열
int top; // 스택 상단 인덱스
void error(char str[])
{
    printf("error() 호출 스택 삽입\n");
    printf("%s\n", str);
    printf("error() 호출 스택 삭제\n");
    exit(1);
}
// 스택의 주요 연산들
void init_stack()
{
    printf("init_stack() 호출 스택 삽입\n");
    top = -1;
    printf("init_stack() 호출 스택 삭제\n");
}
int is_empty()
{
    printf("is_empty() 호출 스택 삽입\n");
    if (top == -1)
    {
        printf("is_empty() 호출 스택 삭제\n");
        return 1;
    }
    else 
    {
        printf("is_empty() 호출 스택 삭제\n");
        return 0;
    }
}
int is_full()
{
    printf("is_full() 호출 스택 삽입\n");
    printf("is_full() 호출 스택 삭제\n");
    return (top == (MAX_SIZE - 1));
}
void push(Element e)
{
    printf("push() 호출 스택 삽입\n");
    if (is_full())
        error("Overflow Error!");
    else data[++top] = e;
    printf("push() 호출 스택 삭제\n");
}
Element pop()
{
    printf("pop() 호출 스택 삽입\n");
    if (is_empty())
        error("Underflow Error!");
    printf("pop() 호출 스택 삭제\n");
    return data[top--];
}
Element peek()
{
    printf("peek() 호출 스택 삽입\n");
    if (is_empty())
        error("Underflow Error!");
    printf("peek() 호출 스택 삭제\n");
    return data[top];
}

int size()
{
    printf("size() 호출 스택 삽입\n");
    printf("size() 호출 스택 삭제\n");
    return top + 1;
}
