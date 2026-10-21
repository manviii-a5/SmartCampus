
#ifdef __cplusplus
extern "C" {
#endif
#ifndef BST_H
#define BST_H

typedef struct BSTNode
{
    long long key;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode* createBSTNode(long long key);

BSTNode* insertBST(BSTNode *root, long long key);

BSTNode* searchBST(BSTNode *root, long long key);

BSTNode* findMinimum(BSTNode *root);

BSTNode* deleteBST(BSTNode *root, long long key);

void inorderBST(BSTNode *root);

void preorderBST(BSTNode *root);

void postorderBST(BSTNode *root);

void freeBST(BSTNode *root);

#endif
#ifdef __cplusplus
}
#endif
