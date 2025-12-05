/*
 *  This hw is made to implement a fibonacci heap in C
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "fibonacci_heap.h"

#define MAX_DEGREE 128

typedef struct FibNode FibNode;
struct FibNode {
    int value;
    int degree;
    bool childCut;
    FibNode *parent;
    FibNode *leftSibling;
    FibNode *rightSibling;
    FibNode *children;
};
typedef struct FibHeap FibHeap;
struct FibHeap {
    FibNode *min;
    size_t nodeCount;
};

/**
 * @brief Create a new empty Fibonacci Heap
 */
FibHeap *createHeap(void) {
    FibHeap *heap = malloc(sizeof(FibHeap));
    if (heap) {
        heap->min = NULL;
        heap->nodeCount = 0;
    }
    return heap;
}
/**
 * @brief Construct a new Fibonacci Node
 */
static FibNode *newNode(int const value) {
    FibNode *node = malloc(sizeof(FibNode));
    node->value = value;
    node->degree = 0;
    node->childCut = false;
    node->parent = NULL;
    node->leftSibling = node;
    node->rightSibling = node;
    node->children = NULL;
    return node;
}
/**
 * @brief A function that adds a node to the root list of the fibonacci heap
 */
static void addToRootList(FibHeap *heap, FibNode *node) {
    node->parent = NULL;
    node->childCut = false;
    if (!heap->min) {
        node->leftSibling = node;
        node->rightSibling = node;
        heap->min = node;
    } else {
        node->rightSibling = heap->min->rightSibling;
        node->leftSibling = heap->min;
        heap->min->rightSibling->leftSibling = node;
        heap->min->rightSibling = node;
        if (node->value < heap->min->value) {
            heap->min = node;
        }
    }
}
/**
 * @brief A function that removes a node from a Circular Doubly Linked List
 */
static void removeFromList(FibNode *node) {
    node->leftSibling->rightSibling = node->rightSibling;
    node->rightSibling->leftSibling = node->leftSibling;
    node->rightSibling = node;
    node->leftSibling = node;
}
/**
 * @brief A function that merges two fibonacci tree by making y a child of x, According to Heap property
 * @param y The node to be made child
 * @param x The node to be made parent
 * @return void
 */
static void fibHeapLink(FibNode *y, FibNode *x) {
    removeFromList(y);
    y->parent = x;
    y->childCut = false;
    if (!x->children) {
        x->children = y;
        y->leftSibling = y;
        y->rightSibling = y;
    } else {
        FibNode *child = x->children;
        y->rightSibling = child->rightSibling;
        y->leftSibling = child;
        child->rightSibling->leftSibling = y;
        child->rightSibling = y;
    }
    x->degree++;
}
/**
 * @brief Implement the consolidate method by merging trees of the same degree recursively
 * @return void
 */
static void consolidate(FibHeap *heap) {
    if (!heap->min) return;

    FibNode *start = heap->min, *c = start;
    int rootCount = 0;
    do {
        rootCount++;
        c = c->rightSibling;
    } while (c != start);

    FibNode **roots = malloc(rootCount * sizeof(FibNode *));
    c = start;
    for (int i = 0; i < rootCount; i++) {
        roots[i] = c;
        c = c->rightSibling;
    }
    FibNode *A[MAX_DEGREE] = { NULL };
    for (int i = 0; i < rootCount; i++) {
        FibNode *curr = roots[i];
        int degree = curr->degree;
        while (degree < MAX_DEGREE && A[degree] != NULL) {
            FibNode *other = A[degree];
            if (curr->value > other->value) {
                FibNode *temp = curr;
                curr = other;
                other = temp;
            }
            fibHeapLink(other, curr);   // current is made always smaller than other
            A[degree] = NULL;
            degree++;
        }
        if (A[degree] == NULL) {    // Only assign if slot A[degree] is empty
            A[degree] = curr;
        }
    }

    // Refresh min pointer and root list
    heap->min = NULL;
    for (int i = 0; i < MAX_DEGREE; i++) {
        if (A[i] != NULL) {
            A[i]->leftSibling = A[i];
            A[i]->rightSibling = A[i];
            addToRootList(heap, A[i]);
        }
    }
    free(roots);
}
/**
 * @brief A function that cuts the child from its tree and move it into the root list.
 * @param heap The pointer to the operated fibonacci heap
 * @param x The node to be made child.
 * @param y The node to be made parent.
 * @return void
 */
static void cut(FibHeap *heap, FibNode *x, FibNode *y) {
    if (y->children == x) {
        if (x->rightSibling == x) {
            y->children = NULL;
        } else {
            y->children = x->rightSibling;
        }
    }
    removeFromList(x);
    y->degree--;
    x->leftSibling = x;
    x->rightSibling = x;
    addToRootList(heap, x);
}
/**
 * @brief The most important function in fibonacci heap that maintains the structure with O(log n) amortized complexity.
 */
static void cascadingCut(FibHeap *heap, FibNode *y) {
    if (!y) return;
    FibNode *p = y->parent;
    // No parent -> in root -> no more cascading cut
    if (p != NULL) {
        if (y->childCut == false) y->childCut = true;
        else {
            cut(heap, y, p);
            cascadingCut(heap, p);
        }
    }
}

/* --- Public Functions --- */

/**
 * @brief Find a node in the given f-heap
 * @param head The most significant entry of the fibonacci heap
 * @param key The value to be found
 * @return The pointer to the found node, NULL if not found
 */
FibNode *findNodeInList(FibNode *head, int const key) {
    if (head == NULL) return NULL;
    FibNode *curr = head;
    do {
        if (curr->value == key) return curr;
        FibNode *res = findNodeInList(curr->children, key);
        if (res != NULL) return res;
        curr = curr->rightSibling;
    } while (curr != head);
    return NULL;    // result not found
}

FibNode* insertHeap(FibHeap *heap, int const value) {
    FibNode *node = newNode(value);
    addToRootList(heap, node);
    heap->nodeCount++;
    return node;
}

void extractMin(FibHeap *heap) {
    FibNode *z = heap->min;
    if (!z) {
        fprintf(stderr, "extractMin: empty heap\n");
        return;
    }
    if (z->children) {
        FibNode *start = z->children;
        FibNode *curr = start;
        do {
            FibNode *next = curr->rightSibling;
            curr->childCut = false;
            curr->parent = NULL;
            curr->rightSibling = curr;
            curr->leftSibling = curr;
            addToRootList(heap, curr);
            curr = next;
        } while (curr != start);
        z->children = NULL;
    }
    if (z->rightSibling == z) {
        heap->min = NULL;
    } else {
        heap->min = z->rightSibling;
        removeFromList(z);
        consolidate(heap);
    }
    heap->nodeCount--;
    free(z);
}

void decreaseKey(FibHeap *heap, FibNode *x, int const newValue) {
    if (!heap->min || !x) return;
    if (newValue > x->value) {
        fprintf(stderr, "New key is greater than current key\n");
        return;
    }

    x->value = newValue;
    FibNode *y = x->parent;
    // CLRS Rule: If heap property violated, cut and cascading cut
    if (y != NULL && x->value < y->value) {
        cut(heap, x, y);
        cascadingCut(heap, y);
    }
    // Update global min if necessary
    if (x->value < heap->min->value) {
        heap->min = x;
    }
}

void deleteNode(FibHeap *heap, FibNode *x) {
    decreaseKey(heap, x, INT_MIN);
    extractMin(heap);
}