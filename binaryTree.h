#pragma once

struct BinaryTreeNode {
    void* data;
    size_t dataSize;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
};

struct BinaryTreeNode* createNode(struct BinaryTreeNode* root, void* value, size_t size);
int addNode(struct BinaryTreeNode** root, void* value, size_t dataSize);
struct BinaryTreeNode* searchNode(struct BinaryTreeNode* root, void* value);
struct BinaryTreeNode* removeNode(struct BinaryTreeNode* root, void* value);
struct BinaryTreeNode* getMinNode(struct BinaryTreeNode* root);
void destroyTree(struct BinaryTreeNode* root);