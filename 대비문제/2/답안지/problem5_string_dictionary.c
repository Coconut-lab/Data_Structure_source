// 문제 5: 문자열 해시 테이블 구현
// hash_chain.c를 참고하여 문자열을 키로 하는 사전(Dictionary) 구현

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hash_chain의 구조 확장
typedef struct DictNode {
    char key[50];      // 문자열 키
    char value[100];   // 문자열 값
    struct DictNode* next;  // 다음 노드 포인터 (체이닝)
} DictNode;

#define DICT_SIZE 17    // 해시 테이블 크기 (소수 사용)
DictNode* dictionary[DICT_SIZE];  // 해시 테이블

// 해시 테이블 초기화
void init_dictionary() {
    for (int i = 0; i < DICT_SIZE; i++) {
        dictionary[i] = NULL;
    }
}

// 문자열 해시 함수 구현
// 각 문자의 ASCII 값을 이용한 해시 함수
int string_hash(char* str) {
    int hash_value = 0;
    int len = strlen(str);
    
    // 방법 1: 간단한 합산 방식
    for (int i = 0; i < len; i++) {
        hash_value += str[i];
    }
    
    // 방법 2: 더 나은 해시 함수 (호너의 방법)
    // hash_value = 0;
    // for (int i = 0; i < len; i++) {
    //     hash_value = (hash_value * 31 + str[i]) % DICT_SIZE;
    // }
    
    return hash_value % DICT_SIZE;
}

// 새로운 딕셔너리 노드 생성
DictNode* create_dict_node(char* key, char* value) {
    DictNode* new_node = (DictNode*)malloc(sizeof(DictNode));
    if (new_node == NULL) {
        printf("메모리 할당 실패!\n");
        return NULL;
    }
    
    strcpy(new_node->key, key);
    strcpy(new_node->value, value);
    new_node->next = NULL;
    
    return new_node;
}

// 딕셔너리에 키-값 쌍 추가
// hash_chain의 insert_chain 참고하여 구현
void dict_put(char* key, char* value) {
    int index = string_hash(key);  // 해시 주소 계산
    
    // 기존에 같은 키가 있는지 확인 (업데이트 처리)
    DictNode* current = dictionary[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // 같은 키 발견 - 값 업데이트
            strcpy(current->value, value);
    
            return;
        }
        current = current->next;
    }
    
    // 새로운 키-값 쌍 추가 (체인의 맨 앞에 삽입)
    DictNode* new_node = create_dict_node(key, value);
    if (new_node == NULL) return;
    
    new_node->next = dictionary[index];  // 기존 체인 연결
    dictionary[index] = new_node;        // 새 노드를 헤드로 설정
    

}

// 딕셔너리에서 키에 해당하는 값 검색
// hash_chain의 search_chain 참고하여 구현
char* dict_get(char* key) {
    int index = string_hash(key);  // 해시 주소 계산
    
    // 해당 인덱스의 체인을 순회하며 검색
    DictNode* current = dictionary[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // 키 발견 - 값 반환

            return current->value;
        }
        current = current->next;
    }
    
    // 키를 찾지 못함

    return NULL;
}

// 딕셔너리에서 키-값 쌍 삭제
// hash_chain의 delete_chain 참고하여 구현
void dict_remove(char* key) {
    int index = string_hash(key);  // 해시 주소 계산
    DictNode* current = dictionary[index];
    
    if (current == NULL) {
    
        return;
    }
    
    // 첫 번째 노드가 삭제 대상인 경우
    if (strcmp(current->key, key) == 0) {
        dictionary[index] = current->next;

        free(current);
        return;
    }
    
    // 나머지 노드들 중에서 삭제 대상 찾기
    while (current->next != NULL) {
        if (strcmp(current->next->key, key) == 0) {
            DictNode* node_to_delete = current->next;
            current->next = node_to_delete->next;

            free(node_to_delete);
            return;
        }
        current = current->next;
    }
    

}

// 특정 키가 존재하는지 확인
int dict_contains(char* key) {
    return dict_get(key) != NULL;
}

// 딕셔너리 전체 출력
void print_dictionary() {
    printf("\n=== 딕셔너리 전체 내용 ===\n");
    int total_items = 0;
    
    for (int i = 0; i < DICT_SIZE; i++) {
        printf("인덱스 %2d: ", i);
        
        DictNode* current = dictionary[i];
        if (current == NULL) {
            printf("(비어있음)\n");
        } else {
            while (current != NULL) {
                printf("[%s:%s]", current->key, current->value);
                if (current->next != NULL) printf(" -> ");
                current = current->next;
                total_items++;
            }
            printf("\n");
        }
    }
    
    printf("총 %d개 항목\n", total_items);
}

// 해시 테이블 통계 출력
void print_hash_statistics() {
    int non_empty_buckets = 0;
    int max_chain_length = 0;
    int total_items = 0;
    
    for (int i = 0; i < DICT_SIZE; i++) {
        int chain_length = 0;
        DictNode* current = dictionary[i];
        
        while (current != NULL) {
            chain_length++;
            total_items++;
            current = current->next;
        }
        
        if (chain_length > 0) {
            non_empty_buckets++;
            if (chain_length > max_chain_length) {
                max_chain_length = chain_length;
            }
        }
    }
    
    printf("\n=== 해시 테이블 통계 ===\n");
    printf("전체 버킷 수: %d\n", DICT_SIZE);
    printf("사용된 버킷 수: %d\n", non_empty_buckets);
    printf("총 항목 수: %d\n", total_items);
    printf("최대 체인 길이: %d\n", max_chain_length);
    printf("부하율: %.2f\n", (double)total_items / DICT_SIZE);
}

// 메모리 해제
void destroy_dictionary() {
    for (int i = 0; i < DICT_SIZE; i++) {
        DictNode* current = dictionary[i];
        while (current != NULL) {
            DictNode* temp = current;
            current = current->next;
            free(temp);
        }
        dictionary[i] = NULL;
    }
    printf("딕셔너리 메모리 해제 완료\n");
}

// 테스트 함수
void test_string_dictionary() {
    init_dictionary();
    
    // 기본 삽입
    dict_put("apple", "사과");
    dict_put("banana", "바나나");
    dict_put("cherry", "체리");
    dict_put("grape", "포도");
    dict_put("orange", "오렌지");
    
    // 검색 테스트
    printf("검색 결과:\n");
    printf("apple: %s\n", dict_get("apple"));
    printf("banana: %s\n", dict_get("banana"));
    
    // 업데이트
    dict_put("apple", "빨간 사과");
    printf("apple 업데이트: %s\n", dict_get("apple"));
    
    // 삭제
    dict_remove("banana");
    printf("banana 삭제 후: %s\n", dict_get("banana") ? dict_get("banana") : "NULL");
    
    destroy_dictionary();
}

int main() {
    test_string_dictionary();
    return 0;
}
