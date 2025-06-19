#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    double Nt;
    struct Node* left;
    struct Node* right;
} NODE;

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

void inorder_traversal(NODE* root, FILE* fp) {
    if (root != NULL) {
        inorder_traversal(root->left, fp);
        fprintf(fp, "%.4lf\n", root->Nt);
        printf("%.4lf\n", root->Nt);
        inorder_traversal(root->right, fp);
    }
}

void free_tree(NODE* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int get_height(NODE* root) {
    if (root == NULL) return 0;
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

void print_tree(NODE* root, int space) {
    if (root == NULL) return;
    
    space += 5;
    
    print_tree(root->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%.4lf\n", root->Nt);
    
    print_tree(root->left, space);
}

int main() {
    FILE* input_file = fopen("01.txt", "r");
    if (input_file == NULL) {
        printf("01.txt 파일을 열 수 없습니다.\n");
        printf("01.c를 먼저 실행해주세요.\n");
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
        printf("데이터가 없습니다. 01.c를 먼저 실행해주세요.\n");
        return 1;
    }

    int mid_index = (count - 1) / 2;
    NODE* root = build_balanced_bst(array1, 0, count - 1);

    FILE* output_file = fopen("02.txt", "w");
    if (output_file == NULL) {
        printf("\n02.txt 파일을 생성할 수 없습니다.\n");
        free_tree(root);
        return 1;
    }
    
    printf("=== 중위 순회 결과 ===\n");
    inorder_traversal(root, output_file);
    
    fclose(output_file);

    free_tree(root);
    
    printf("\n'02.txt' 파일에 저장되었습니다.\n");
    system("open 02.txt");
    
    return 0;
}