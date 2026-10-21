#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTNode* createBSTNode(long long key)
{
    BSTNode *newNode =
        (BSTNode*)malloc(sizeof(BSTNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

BSTNode* insertBST(BSTNode *root, long long key)
{
    if (root == NULL)
        return createBSTNode(key);

    if (key < root->key)
        root->left = insertBST(root->left, key);

    else if (key > root->key)
        root->right = insertBST(root->right, key);

    return root;
}

BSTNode* searchBST(BSTNode *root, long long key)
{
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchBST(root->left, key);

    return searchBST(root->right, key);
}

BSTNode* findMinimum(BSTNode *root)
{
    if (root == NULL)
        return NULL;

    BSTNode *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

BSTNode* deleteBST(BSTNode *root, long long key)
{
    if (root == NULL)
        return NULL;

    if (key < root->key)
    {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteBST(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL)
        {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }

        BSTNode *temp = findMinimum(root->right);

        root->key = temp->key;

        root->right =
            deleteBST(root->right, temp->key);
    }

    return root;
}

void inorderBST(BSTNode *root)
{
    if (root == NULL)
        return;

    inorderBST(root->left);
    printf("%lld ", root->key);
    inorderBST(root->right);
}

void preorderBST(BSTNode *root)
{
    if (root == NULL)
        return;

    printf("%lld ", root->key);
    preorderBST(root->left);
    preorderBST(root->right);
}

void postorderBST(BSTNode *root)
{
    if (root == NULL)
        return;

    postorderBST(root->left);
    postorderBST(root->right);
    printf("%lld ", root->key);
}

void freeBST(BSTNode *root)
{
    if (root == NULL)
        return;

    freeBST(root->left);
    freeBST(root->right);

    free(root);
}