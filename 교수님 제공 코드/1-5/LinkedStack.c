// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch05/LinkedStack.c


//-------------------------------------------------------------
// 코드 5.4 연결된 스택의 활용


#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#include "LinkedStack.h"

//-------------------------------------------------------------
// 코드 5.7 스택 요소를 입력순으로 출력
void print_stack()
{
    for (Node* p = top; p != NULL; p = p->link) {
        printf("%3d", p->data);
    }
}

void print_recur(Node* p)
{
    if (p != NULL) {
        print_recur(p->link);
        printf("%3d", p->data);
    }
}


void main()
{
    int A[7] = { 0, 1, 1, 2, 3, 5, 8 };

    init_stack();
    printf("스택 테스트\n 입력 데이터: ");
    for (int i = 0; i < 7; i++) {
        printf("%3d", A[i]);
        push(A[i]);
    }

    /*
    printf("\n입력된 순서");
    print_recur(top);
    printf("\n입력의 역순");
    print_stack();
    printf("\n");
    */

    printf("\n 출력 데이터: ");
    while (!is_empty())
        printf("%3d", pop());
    printf("\n");

    destroy_stack();
}
