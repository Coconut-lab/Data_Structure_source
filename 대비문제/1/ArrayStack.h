// �αٵα� �ڷᱸ�� ������(�ֿ���, ���� ���ǻ�)
// �������� ch03/ArrayStack.h

//-------------------------------------------------------------
// �ڵ� 3.1 �迭�� �̿��� ������ ����


// ������ ������(Element�� MAX_SIZE�� �̸� ���ǵǾ� �־�� ��)
Element data[MAX_SIZE]; // ���� ����� �迭
int top; // ���� ��� �ε���
void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}
// ������ �ֿ� �����
void init_stack()
{
    top = -1;
}
int is_empty()
{
    if (top == -1) return 1;
    else return 0;
}
int is_full()
{
    return (top == (MAX_SIZE - 1));
}
void push(Element e)
{
    if (is_full())
        error("Overflow Error!");
    else data[++top] = e;
}
Element pop()
{
    if (is_empty())
        error("Underflow Error!");
    return data[top--];
}
Element peek()
{
    if (is_empty())
        error("Underflow Error!");
    return data[top];
}

int size()
{
    return top + 1;
}
