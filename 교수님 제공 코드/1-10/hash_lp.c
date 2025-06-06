// 쉽게 배우는 C자료구조(최영규, 생능 출판사, 2024)
// 참고파일 ch10/hash_lp.c

//--------------------------------------------------------------------
// 코드 10.5 선형 조사법


#include <stdio.h>
typedef int Entry;  // 테이블에 저장할 엔트리
#define M   13      // 해시 테이블의 크기
Entry table[M];     // 해시 테이블
int hashFn(Entry key) { return key % M; }

void init_lp() {                // 테이블 초기화 함수
    for (int i = 0; i < M; i++) // 모든 버킷을 0(사용 안 됨)으로 초기화
        table[i] = 0;

    // 인덱스 출력용 코드 추가
    printf("인덱스");			// 인덱스 출력용 코드
    for (int i = 0; i < M; i++)
        printf("%5d", i);
    printf("\n");

}
void print_lp(const char* msg)  // 테이블 출력을 위한 함수
{
    printf("%s: ", msg);
    for (int i = 0; i < M; i++)
        printf("[%2d] ", table[i]);
    printf("\n");
}

void insert_lp(Entry key) {
    int i = hashFn(key);        // 해시 주소 계산
    for (int k = 0; k < M; k++) {
        if (table[i] == 0 || table[i] == -1) {
            table[i] = key;
            return;
        }
        i = (i + 1) % M;        // 다음에 조사할 위치
    }
}

int search_lp(Entry key) {
    int i = hashFn(key);        // 해시 주소 계산
    for (int k = 0; k < M; k++) {
        if (table[i] == key) return i;
        if (table[i] == 0) return -1;
        i = (i + 1) % M;        // 다음에 조사할 위치
    }
    return -1;                  // 모든 테이블을 검사했으면 탐색 실패: -1 반환
}

int delete_lp(Entry key) {
    int i = hashFn(key);        // 해시 주소 계산
    for (int k = 0; k < M; k++) {
        if (table[i] == key) {
            table[i] = -1;
            return i;
        }
        if (table[i] == 0)      // 탐색 실패: -1 반환
            return -1;
        i = (i + 1) % M;        // 다음에 조사할 위치
    }
    return -1;                  // 모든 테이블을 검사했으면 탐색 실패: -1 반환
}

void main()
{
    Entry data[9] = { 45, 27, 88, 9, 71, 60, 46, 38, 24 };
    init_lp();
    print_lp("삽입전");
    for (int i = 0; i < 9; i++) {
        insert_lp(data[i]);
        print_lp(" ");
    }
    printf("46탐색: %d\n", search_lp(46));
    printf("39탐색: %d\n", search_lp(39));
    delete_lp(60); print_lp("60삭제");
    delete_lp(46); print_lp("46삭제");
}
