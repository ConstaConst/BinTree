#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"
#include <string.h>

struct BinaryTreeNode* searchNode(struct BinaryTreeNode* root, void* value) {
    if (!root)
        return NULL;
    int comparison = memcmp(value, root->data, root->dataSize);
    if (!comparison)
        return root;
    if (comparison > 0)
        return searchNode(root->right, value);
    else
        return searchNode(root->left, value);
}
struct BinaryTreeNode* getMinNode(struct BinaryTreeNode* root) {
    if (!root)
        return NULL;

    while (root->left)
        root = root->left;

    return root;
}
struct BinaryTreeNode* removeNode(struct BinaryTreeNode* root, void* value) {
    struct BinaryTreeNode* temp;
    if (!root)
        return NULL;
    int comparison = memcmp(value, root->data, root->dataSize);

    if (comparison > 0)
        root->right = removeNode(root->right, value);
    if (comparison < 0)
        root->left = removeNode(root->left, value);
    if (!comparison) {
        if (!root->left && !root->right) {
            destroyTree(root);
            return NULL;
        }
        if (root->left && !root->right) {
            temp = root->left;
            free(root->data);
            free(root);
            return temp;
        }
        if (!root->left && root->right) {
            temp = root->right;
            free(root->data);
            free(root);
            return temp;
        }
        if (root->left && root->right) {
            memcpy(value, getMinNode(root->right)->data, root->dataSize);
            root->right = removeNode(root->right, value);
            memcpy(root->data, value, root->dataSize);
        }
    }
    return root;
}


void destroyTree(struct BinaryTreeNode* root) {
    if (root) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root->data);
        free(root);
    }
}

int addNode(struct BinaryTreeNode** root, void* value, size_t dataSize) {
    struct BinaryTreeNode* main_root = *root;

    struct BinaryTreeNode* newNode = NULL;
    newNode = createNode(newNode, value, dataSize);
    if (!newNode) {
        return -1;
    }
    int comparison ;
    while (*root) {
        comparison = memcmp(value, (*root)->data, dataSize);
        if (!comparison) {
            free(newNode);
            (*root) = main_root;
            return 0;
        }
        if (comparison < 0)
            if ((*root)->left) {
                (*root) = (*root)->left;
                continue;
            }
            else {
                (*root)->left = newNode;
                (*root) = main_root;
                return 0;
            }
        {
            if ((*root)->right) {
                (*root) = (*root)->right;
                continue;
            } else {
                (*root)->right = newNode;
                (*root) = main_root;
                return 0;
            }
        }
    }
    (*root) = newNode;
    return 0;
}

struct BinaryTreeNode* createNode(struct BinaryTreeNode* root, void* value, size_t size) {
    root = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    if (!root) {
        return NULL;
    }
    root->data = malloc(size);
    if (!root->data) {
        return NULL;
    }

    root->dataSize = size;
    memcpy(root->data, value, size);
    root->left = NULL;
    root->right = NULL;

    return root;
}