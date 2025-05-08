// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch06/LinkedList.c


//--------------------------------------------------------------------
// 코드 6.5 연결된 구조의 리스트 테스트 프로그램


#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#include "LinkedList.h" // 리스트 데이터와 연산

void print_list(char* msg)
{
    printf("단순연결리스트 %s[%2d]: ", msg, size());
    for (Node* p = head; p != NULL; p = p->link)
        printf("%2d ", p->data);
    printf("\n");
}
void main()
{
    init_list(); // [ ]
    insert(0, 10); // [10]
    insert(0, 20); // [20, 10]
    insert(1, 30); // [20, 30, 10]
    insert(size(), 40); // [20, 30, 10, 40]
    insert(2, 50); // [20, 30, 50, 10, 40]
    print_list("(삽입x5)");

    delete(2); // [20, 30, 10, 40]
    delete(size() - 1); // [20, 30, 10]
    delete(0); // [30, 10]
    print_list("(삭제x3)");
    destroy_list();
}
