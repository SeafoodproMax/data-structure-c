#ifndef DATA_STRUCTURE_C_BST_H
#define DATA_STRUCTURE_C_BST_H

typedef struct BSTNode BSTNode;

BSTNode *createBST(int data);
BSTNode *findMinBST(BSTNode *node);

BSTNode *insertBST(BSTNode *root, int data);
BSTNode *searchBST(BSTNode *root, int data);
BSTNode *deleteNodeBST(BSTNode *root, int data);

#endif
