//
// Created by 林勁博 on 2025/12/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @brief Type definition for the comparison function.
 * returns > 0 if *a has higher priority than *b.
 * * @param a Pointer to the first element (e.g., &data[i]).
 * @param b Pointer to the second element.
 * @return int Positive if a has higher priority, 0 if equal, negative otherwise.
 */
typedef int (*ComparisonFunction)(const void* a, const void* b);

typedef struct Heap Heap;

/**
 * @brief Structure representing a generic-logic Heap.
 * * Uses 1-based indexing (data[0] is unused) for simpler child/parent calculations.
 */
struct Heap {
    int *data;
    size_t size;             ///< Current number of elements in the heap.
    ComparisonFunction comp; ///< Function pointer defining Max/Min Heap logic.
    size_t capacity;         ///< Maximum capacity of the heap (not including index 0).
};

// --- Helper Functions ---

/**
 * @brief Swaps the values of two integers.
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Restores the heap property by moving an element up the tree.
 * * This process is also known as "Bubble Up" or "Sift Up".
 * The comparison logic is determined by the heap->comp function.
 * * @param heap The heap structure.
 * @param i The 1-based index of the element to be moved up.
 */
void heapify_up(Heap *heap, size_t i) {
    while (i > 1) {
        size_t parent_i = i / 2;
        // If the child (i) has higher priority than the parent (parent_i), swap.
        // The comp function abstracts Max vs. Min logic.
        if (heap->comp(&heap->data[i], &heap->data[parent_i]) > 0) {
            swap(&heap->data[i], &heap->data[parent_i]);
            i = parent_i;
        } else {
            break;
        }
    }
}

/**
 * @brief Restores the heap property by moving an element down the tree.
 * * This process is also known as "Bubble Down" or "Sift Down".
 * The comparison logic is determined by the heap->comp function.
 * * @param heap The heap structure.
 * @param i The 1-based index of the element to be moved down.
 */
void heapify_down(Heap *heap, size_t i) {
    while (2 * i <= heap->size) {
        size_t left_child = 2 * i;
        size_t right_child = 2 * i + 1;
        size_t preferred_i = i;
        if (heap->comp(&heap->data[left_child], &heap->data[preferred_i]) > 0) {
            preferred_i = left_child;
        }
        if (right_child <= heap->size &&
            heap->comp(&heap->data[right_child], &heap->data[preferred_i]) > 0) {
            preferred_i = right_child;
        }

        // If the preferred element is a child, swap and continue down.
        if (preferred_i != i) {
            swap(&heap->data[i], &heap->data[preferred_i]);
            i = preferred_i;
        } else {
            break;
        }
    }
}

// --- Public API Functions ---

/**
 * @brief Creates a new Heap instance.
 * * @param max_capacity The maximum number of elements the heap can hold.
 * @param comp The comparison function, returns > 0 if the first has higher priority than the second.
 * @return Heap* A pointer to the newly created Heap structure, or NULL on failure.
 */
Heap *newHeap(size_t max_capacity, ComparisonFunction comp) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    if (!heap) return NULL;

    // Allocate max_capacity + 1 space for 1-based indexing
    heap->data = (int *)malloc(sizeof(int) * (max_capacity + 1));
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = max_capacity;
    heap->comp = comp;

    return heap;
}

/**
 * @brief Frees all memory associated with the Heap.
 * @param heap The heap structure to be freed.
 */
void freeHeap(Heap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

/**
 * @brief Checks if the Heap is empty.
 * @param heap The heap structure.
 * @return bool True if the heap contains no elements, false otherwise.
 */
bool isEmptyHeap(Heap *heap) {
    return heap->size == 0;
}

/**
 * @brief Retrieves the element with the highest priority (the root element).
 * * @param heap The heap structure.
 * @return int The value of the top element. Returns INT_MIN if the heap is empty
 * (handle this edge case carefully in production code).
 */
int topHeap(Heap *heap) {
    if (isEmptyHeap(heap)) {
        return INT_MIN;
    }
    // Root is always at index 1
    return heap->data[1];
}

/**
 * @brief Inserts a new element into the Heap.
 * @param heap The heap structure.
 * @param data The integer value to insert.
 */
void insertHeap(Heap *heap, int data) {
    if (heap->size >= heap->capacity) {
        fprintf(stderr, "Error: Heap is full!\n");
        return;
    }

    heap->size++;
    heap->data[heap->size] = data;
    // Restore heap property by bubbling up the new element
    heapify_up(heap, heap->size);
}

/**
 * @brief Deletes the element with the highest priority (the root element).
 * @param heap The heap structure.
 */
void deleteHeap(Heap *heap) {
    if (isEmptyHeap(heap)) {
        fprintf(stderr, "Error: Heap is empty!\n");
        return;
    }

    heap->data[1] = heap->data[heap->size];
    heap->size--;

    // Restore heap property by bubbling down the new root
    if (heap->size > 0) {
        heapify_down(heap, 1);
    }
}

/*
int min_comp(const void* a, const void* b) {
    // Cast void* to int* and dereference
    return *(const int*)b - *(const int*)a;
}

int max_comp(const void* a, const void* b) {
    return *(const int*)a - *(const int*)b;
}
*/

