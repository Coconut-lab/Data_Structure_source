// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch10/hash_chain.c


//--------------------------------------------------------------------
// 코드 10.6 체이닝


#include <stdio.h>
#include <stdlib.h>
typedef int Entry;      // 테이블에 저장할 엔트리
typedef struct HNode {  // 단순 연결 노드
    Entry key;
    struct HNode* link;
} Node;

#define M   13          // 해시 테이블의 크기
Node* table[M];         // 해시 테이블
int hashFn(Entry key) { return key % M; }

void init_chain() {     // 테이블 초기화 함수
    for (int i = 0; i < M; i++) // 모든 버킷을 NULL로 초기화
        table[i] = NULL;
}
void print_chain(char* msg) {	// 테이블 출력 함수
    printf("%s: ", msg);
    for (int i = 0; i < M; i++) {
        printf("->");
        for (Node* n = table[i]; n != NULL; n = n->link)
            printf("%2d ", n->key);
        printf(" ");
    }
    printf("\n");
}

void insert_chain(Entry key) {
    int i = hashFn(key);                    // 해시 주소 계산
    Node* n = (Node*)malloc(sizeof(Node));  // 노드 생성
    n->key = key;                           // 엔트리 복사
    n->link = table[i];                     // 맨 앞에 연결
    table[i] = n;
}

Node* search_chain(Entry key) {
    int i = hashFn(key);                    // 해시 주소 계산
    for (Node* n = table[i]; n != NULL; n = n->link)
        if (key == n->key)                  // 탐색 성공: 노드 반환
            return n;
    return NULL;                            // 탐색 실패: NULL 반환
}

void delete_chain(Entry key) {
    int i = hashFn(key);                    // 해시 주소 계산
    Node* n = table[i];                     // 해당 주소의 시작 노드
    if (n == NULL) return;                  // (1) 삭제할 노드가 없는 경우
    if (key == n->key) {                    // (2) 첫 번째 노드 삭제
        table[i] = n->link;
        free(n);
    }
    else {                                  // (3) 그 외: 이전 노드를 알아야 함
        for (; n->link != NULL; n = n->link) {
            if (key == n->link->key) {
                Node* p = n->link;
                n->link = p->link;
                free(p);
                return;
            }
        }
    }
}


void main()
{
    Entry data[9] = { 45, 27, 88, 9, 71, 60, 46, 38, 24 };

    init_chain();
    print_chain("삽입전");

    for (int i = 0; i < 9; i++) {
        insert_chain(data[i]);
        print_chain("      ");
    }

    printf("46탐색: %p\n", search_chain(46));
    printf("39탐색: %p\n", search_chain(39));

    delete_chain(60);	print_chain("60삭제");
    delete_chain(45);	print_chain("45삭제");
}
