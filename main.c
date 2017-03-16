#include <stdio.h>
#include "binaryTree.h"

int read_file(FILE *ft, struct BinaryTreeNode **root);
void printSortAscending(struct BinaryTreeNode* root);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("ERROR! Filename is absent.\n");
        return -1;
    }

    FILE *ft = fopen(argv[1], "r");
    if (!ft) {
        printf("ERROR! File doesn't open.\n");
        return -1;
    }

    struct BinaryTreeNode *root = NULL;

    if (read_file(ft, &root)) {
        return -1;
    }
    fclose(ft);

    destroyTree(root);
    return 0;
}

int read_file(FILE *ft, struct BinaryTreeNode **root) {
    char c;
    unsigned long long number = 0;

    while((c = getc(ft)) != EOF)
        if ((c == '+') || (c == '-') || (c == '?')) {
            if (fscanf(ft, "%llu", &number) != 1) {
                printf("ERROR! Number hasn't been scanned!\n");
                continue;
            }
            if (c == '+') {
                if(addNode(root, &number, sizeof(long long))) {
                    printf("ERROR! No memory! %llu hasn't been added.\n", number);
                    return -1;
                }
                printSortAscending(*root);////
                printf("\n");
            }
            if (c == '-') {
                *root = removeNode(*root, &number);
                printSortAscending(*root);////
                printf("\n");
            }
            if (c == '?') {
                if(searchNode(*root, &number))
                    printf("%llu - YES\n", number);
                else
                    printf("%llu - NO\n", number);
            }
        }
    return 0;
}

void printSortAscending(struct BinaryTreeNode* root) {
    if (!root)
        return;

    printSortAscending(root->left);
    printf("%llu ", *(unsigned long long*)root->data);
    printSortAscending(root->right);
}