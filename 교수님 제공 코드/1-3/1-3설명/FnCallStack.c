// 명품 열혈 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch03/FnCallStack.c

//-------------------------------------------------------------
// 코드 3.4 스택에 구조체 저장하기
//-------------------------------------------------------------
/*
 * [프로그램 설명]
 * 이 프로그램은 스택을 사용하여 함수 호출의 과정을 시뮬레이션합니다.
 * 재귀 함수 호출 시 시스템이 내부적으로 사용하는 호출 스택(call stack)의 
 * 동작 방식을 이해하기 위한 예제입니다.
 * 
 * [프로그램 목적]
 * factorial(3)의 재귀 호출 과정을 보여줍니다:
 * main() -> factorial(3) -> factorial(2) -> factorial(1)
 * 그리고 반환 과정:
 * factorial(1) -> factorial(2) -> factorial(3) -> main()
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

/*
 * [구조체 정의: CallInfo]
 * 함수 호출 정보를 저장하기 위한 구조체
 * - name: 함수 이름
 * - param: 함수에 전달된 매개변수 값
 */
struct CallInfo { // 함수 호출 정보
    char name[32]; // 함수이름
    int param; // 매개 변수
};
typedef struct CallInfo Element;  // 스택에 저장할 요소 타입을 구조체로 정의
#include "ArrayStack.h"

void main()
{
    // 함수 호출 정보 배열 초기화 (factorial(3)의 재귀 호출 과정을 시뮬레이션)
    Element calls[4] = {
        { "main()" },           // main()함수 호출
        { "factorial()", 3 },   // factorial(3) 호출
        { "factorial()", 2 },   // factorial(2) 호출
        { "factorial()", 1 } }; // factorial(1) 호출

    init_stack();  // 스택 초기화
    
    // 함수 호출 과정 시뮬레이션 (호출 순서대로 스택에 push)
    printf("함수 호출 순서: \n");
    for (int i = 0; i < 4; i++) {
        push(calls[i]);  // 함수 호출 정보를 스택에 저장
        printf("\t%s %d\n", calls[i].name, calls[i].param);
    }
    
    /*
     * [스택 상태 시각화]
     * 모든 함수가 호출된 후의 스택 상태 (위가 스택의 top)
     * +----------------------+
     * | factorial() 1        | ← top
     * +----------------------+
     * | factorial() 2        |
     * +----------------------+
     * | factorial() 3        |
     * +----------------------+
     * | main()               |
     * +----------------------+
     */

    // 함수 반환 과정 시뮬레이션 (스택에서 pop하여 역순으로 반환)
    printf("함수 반환 순서: \n");
    while (!is_empty()) {
        Element call = pop();  // 스택에서 가장 최근 호출 정보를 꺼냄
        printf("\t%s %d\n", call.name, call.param);
    }
    
    /*
     * [실행 결과 분석]
     * 함수 호출 순서:
     *      main() 0
     *      factorial() 3
     *      factorial() 2
     *      factorial() 1
     * 
     * 함수 반환 순서:
     *      factorial() 1
     *      factorial() 2
     *      factorial() 3
     *      main() 0
     * 
     * [스택의 응용: 호출 스택]
     * 이 예제는 실제 프로그램 실행 시 시스템이 함수 호출을 관리하는 방식을 보여줍니다.
     * 시스템은 함수 호출 시 함수의 반환 주소, 매개변수, 지역 변수 등을 스택에 저장합니다.
     * 함수 종료 시 스택에서 이 정보를 꺼내어 이전 함수로 돌아갑니다.
     * 이러한 메커니즘이 재귀 함수 호출을 가능하게 합니다.
     * 
     * [참고] 구조체를 스택에 저장하는 방법
     * 이 예제에서는 스택의 Element 타입을 구조체로 정의하여 
     * 복잡한 데이터(함수 이름과 매개변수)를 함께 저장하는 방법을 보여줍니다.
     */
}
