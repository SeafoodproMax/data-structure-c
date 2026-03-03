#ifndef DATA_STRUCTURE_C_HEAP_H
#define DATA_STRUCTURE_C_HEAP_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Comparison function used to define heap priority.
 *
 * Returns a positive value if `a` has higher priority than `b`.
 */
typedef int (*ComparisonFunction)(const void *a, const void *b);

/**
 * @brief Opaque binary heap type.
 */
typedef struct Heap Heap;

/**
 * @brief Creates a new heap instance.
 *
 * @param max_capacity The maximum number of elements the heap can hold.
 * @param comp Comparison function that defines heap ordering.
 * @return Heap* A pointer to the newly created heap, or NULL on allocation failure.
 */
Heap *newHeap(size_t max_capacity, ComparisonFunction comp);

/**
 * @brief Frees all memory associated with the heap.
 *
 * @param heap The heap structure to be freed.
 */
void freeHeap(Heap *heap);

/**
 * @brief Checks whether the heap contains any elements.
 *
 * @param heap The heap structure.
 * @return true if the heap is empty.
 * @return false otherwise.
 */
bool isEmptyHeap(Heap *heap);

/**
 * @brief Returns the root element with the highest priority.
 *
 * @param heap The heap structure.
 * @return int The top element, or `INT_MIN` if the heap is empty.
 */
int topHeap(Heap *heap);

/**
 * @brief Inserts a new element into the heap.
 *
 * @param heap The heap structure.
 * @param data The integer value to insert.
 */
void insertHeap(Heap *heap, int data);

/**
 * @brief Deletes the root element with the highest priority.
 *
 * @param heap The heap structure.
 */
void deleteHeap(Heap *heap);

#endif
