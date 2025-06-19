#include <stdio.h>
#include <stdlib.h>

#define MAX_DANGEROUS 100

typedef struct Node {
    double Nt;
    struct Node* left;
    struct Node* right;
} NODE;

double dangerous_values[MAX_DANGEROUS];
int dangerous_count = 0;

NODE* create_node(double value) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    if (new_node == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    new_node->Nt = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

NODE* build_balanced_bst(double arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    int mid = (start + end) / 2;
    NODE* root = create_node(arr[mid]);
    
    root->left = build_balanced_bst(arr, start, mid - 1);
    root->right = build_balanced_bst(arr, mid + 1, end);
    
    return root;
}

void find_dangerous(NODE* root, double threshold) {
    if (root == NULL) {
        return;
    }
    find_dangerous(root->left, threshold);
    if (root->Nt >= threshold) {
        dangerous_values[dangerous_count++] = root->Nt;
    }
    
    find_dangerous(root->right, threshold);
}

typedef struct StackNode {
    NODE* tree_node;
    struct StackNode* next;
} StackNode;

void find_dangerous_banbok(NODE* root, double threshold) {
    if (root == NULL) return;
    
    StackNode* stack = NULL;
    NODE* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            StackNode* new_stack_node = (StackNode*)malloc(sizeof(StackNode));
            new_stack_node->tree_node = current;
            new_stack_node->next = stack;
            stack = new_stack_node;
            
            current = current->left;
        }

        if (stack != NULL) {
            StackNode* temp = stack;
            current = temp->tree_node;
            stack = stack->next;
            free(temp);

            if (current->Nt >= threshold) {
                dangerous_values[dangerous_count++] = current->Nt;
            }

            current = current->right;
        }
    }
}

void free_tree(NODE* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    FILE* input_file = fopen("01.txt", "r");
    if (input_file == NULL) {
        printf("01.txt 파일을 열 수 없습니다.\n");
        return 1;
    }
    
    double array1[10];
    int count = 0;
    char line[200];
    double n0, k, t, nt;

    fgets(line, sizeof(line), input_file);
    fgets(line, sizeof(line), input_file);

    while (fscanf(input_file, "%lf %lf %lf %lf", &n0, &k, &t, &nt) == 4 && count < 10) {
        array1[count] = nt;
        count++;
    }
    
    fclose(input_file);
    
    if (count == 0) {
        printf("데이터가 없습니다.\n");
        return 1;
    }

    NODE* root = build_balanced_bst(array1, 0, count - 1);
    double threshold = 90.00;
    char continue_check;
    

    find_dangerous_banbok(root, threshold);

    printf("임계값 %.2f 이상인 위험 샘플: %d개\n", threshold, dangerous_count);
        if (dangerous_count > 0) {
            printf("위험 값들: ");
            for (int i = 0; i < dangerous_count; i++) {
                printf("%.4f ", dangerous_values[i]);
            }
            printf("\n");
        } else {
            printf("위험 샘플이 없습니다.\n");
        }

        FILE* output_file = fopen("04.txt", "w");
        
        fprintf(output_file, "위험 임계값: %.2f\n", threshold);
        for (int i = 0; i < dangerous_count; i += 2) {
            if (i + 1 < dangerous_count) {
                fprintf(output_file, "위험 샘플 N(t)값%02d: %.2f  위험 샘플 N(t)값%02d: %.2f\n", 
                        i + 1, dangerous_values[i], i + 2, dangerous_values[i + 1]);
            } else {
                fprintf(output_file, "위험 샘플 N(t)값%02d: %.2f\n", 
                        i + 1, dangerous_values[i]);
            }
        }
        
        fclose(output_file);
        
        printf("\n'04.txt' 파일에 저장되었습니다.\n");

    
    // 메모리 해제
    free_tree(root);
    system("open 04.txt");
    
    return 0;
}