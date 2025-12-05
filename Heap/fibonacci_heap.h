//
// Created by 林勁博 on 2025/12/5.
//

#ifndef TEMPLATE_FIBONACCI_HEAP_H
#define TEMPLATE_FIBONACCI_HEAP_H

typedef struct FibNode FibNode;
typedef struct FibHeap FibHeap;

FibHeap *createHeap(void);

/**
 * @brief Insert a new value into the fibonacci heap
 * @param heap The pointer to the operated fibonacci heap
 * @param value The value to be inserted
 */
void insertHeap(FibHeap *heap, int value);
/**
 * @brief Extract the minimum value from the fibonacci heap
 * @param heap The pointer to the operated fibonacci heap
 */
void extractMin(FibHeap *heap);
/**
 * @brief Decrease the key of a specific node (Standard CLRS implementation)
 * Time Complexity: O(1) amortized
 * @param heap The pointer to the operated fibonacci heap
 * @param x The pointer to the node to be modified
 * @param newValue The new value to be assigned
 */
void decreaseKey(FibHeap *heap, FibNode *x, int newValue);
/**
 * @brief Delete a node from the fibonacci heap
 * @param heap The pointer to the operated fibonacci heap
 * @param x A pointer to the node to be deleted
 */
void deleteNode(FibHeap *heap, FibNode *x);

#endif //TEMPLATE_FIBONACCI_HEAP_H