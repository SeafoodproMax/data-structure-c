//
// Created by 林勁博 on 2025/12/3.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int data;
    struct BSTNode *leftChild;
    struct BSTNode *rightChild;
} BSTNode;

/**
 * @brief Creates a new BST node. (bst_create_node)
 */
BSTNode* createBST(int data) {
    BSTNode *new_node = malloc(sizeof(BSTNode));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed!!\n");
        return NULL;
    }
    new_node->data = data;
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;
    return new_node;
}

/**
 * @brief Finds the node with the minimum value in a subtree. (bst_find_min)
 */
BSTNode* findMinBST(BSTNode *node) {
    BSTNode *current = node;
    while (current && current->leftChild != NULL) {
        current = current->leftChild;
    }
    return current;
}

// -------------------------------------------------------------------
// Core Operations
// -------------------------------------------------------------------

/**
 * @brief Inserts a new data value into the BST.
 */
BSTNode* insertBST(BSTNode *root, int data) {
    if (root == NULL) {
        return createBST(data);
    }

    if (data < root->data) {
        root->leftChild = insertBST(root->leftChild, data);
    } else if (data > root->data) {
        root->rightChild = insertBST(root->rightChild, data);
    }
    return root;
}

/**
 * @brief Searches for a data value in the BST.
 */
BSTNode* searchBST(BSTNode *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return searchBST(root->leftChild, data);
    } else {
        return searchBST(root->rightChild, data);
    }
}

/**
 * @brief Deletes a node with the given data from the BST.
 */
BSTNode* deleteNodeBST(BSTNode *root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->leftChild = deleteNodeBST(root->leftChild, data);
    } else if (data > root->data) {
        root->rightChild = deleteNodeBST(root->rightChild, data);
    } else {    // Node found
        // degree 0
        if (root->leftChild == NULL && root->rightChild == NULL) {
            free(root);
            return NULL;
        }
        // degree 1
        if (root->leftChild == NULL) {
            BSTNode *temp = root->rightChild;
            free(root);
            return temp;
        } else if (root->rightChild == NULL) {
            BSTNode *temp = root->leftChild;
            free(root);
            return temp;
        }
        // degree 2
        BSTNode *temp = findMinBST(root->rightChild);
        root->data = temp->data;
        root->rightChild = deleteNodeBST(root->rightChild, temp->data);
    }
    return root;
}