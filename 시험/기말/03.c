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

int get_height(NODE* root) {
    if (root == NULL) {
        return 0;
    }

    int left_height = get_height(root->left);
    int right_height = get_height(root->right);

    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

int count_leaves(NODE* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return count_leaves(root->left) + count_leaves(root->right);
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
    int height = get_height(root);
    int leaf_count = count_leaves(root);

    printf("트리 높이: %d\n", height);
    printf("단말 노드 개수: %d\n", leaf_count);

    FILE* output_file = fopen("03.txt", "w");
    if (output_file == NULL) {
        printf("\n03.txt 파일을 생성할 수 없습니다.\n");
        free_tree(root);
        return 1;
    }

    fprintf(output_file, "BST Height: %d", height);
    fprintf(output_file, " ---------- ");
    fprintf(output_file, "Leaf Nodes: %d\n", leaf_count);
    
    fclose(output_file);
    free_tree(root);
    
    printf("'03.txt' 파일에 저장되었습니다.\n");
    system("open 03.txt");
    
    return 0;
}