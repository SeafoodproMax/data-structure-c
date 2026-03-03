#ifndef DATA_STRUCTURE_C_BST_H
#define DATA_STRUCTURE_C_BST_H

/**
 * @brief Opaque binary search tree node type.
 */
typedef struct BSTNode BSTNode;

/**
 * @brief Creates a new BST node.
 *
 * @param data The value stored in the new node.
 * @return BSTNode* Pointer to the newly allocated node, or NULL on allocation failure.
 */
BSTNode *createBST(int data);

/**
 * @brief Finds the node with the minimum value in a subtree.
 *
 * @param node Root of the subtree to inspect.
 * @return BSTNode* Pointer to the minimum node, or NULL if the subtree is empty.
 */
BSTNode *findMinBST(BSTNode *node);

/**
 * @brief Inserts a new value into the BST.
 *
 * @param root Root of the current tree.
 * @param data The value to insert.
 * @return BSTNode* The updated root pointer.
 */
BSTNode *insertBST(BSTNode *root, int data);

/**
 * @brief Searches for a value in the BST.
 *
 * @param root Root of the current tree.
 * @param data The value to search for.
 * @return BSTNode* Pointer to the matching node, or NULL if not found.
 */
BSTNode *searchBST(BSTNode *root, int data);

/**
 * @brief Deletes a value from the BST.
 *
 * @param root Root of the current tree.
 * @param data The value to delete.
 * @return BSTNode* The updated root pointer.
 */
BSTNode *deleteNodeBST(BSTNode *root, int data);

#endif
