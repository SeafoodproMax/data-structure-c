/*
 *  This hw is made to implement a fibonacci heap in C
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "fibonacci_heap.h"


/**
 * @brief Construct a new Fibonacci Node
 */
FibNode *newNode(int const value) {
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
void addToRootList(FibNode *node) {
    node->parent = NULL;
    node->childCut = false;
    if (!min) {
        node->leftSibling = node;
        node->rightSibling = node;
        min = node;
    } else {
        node->rightSibling = min->rightSibling;
        node->leftSibling = min;
        min->rightSibling->leftSibling = node;
        min->rightSibling = node;
        if (node->value < min->value) {
            min = node;
        }
    }
}
/**
 * @brief A function that removes a node from a Circular Doubly Linked List
 */
void removeFromList(FibNode *node) {
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
void fibHeapLink(FibNode *y, FibNode *x) {
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
void consolidate(void) {
    if (!min) return;

    FibNode *start = min, *c = start;
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
    // qsort(roots, rootCount, sizeof(FibNode *), comp);
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
    min = NULL;
    for (int i = 0; i < MAX_DEGREE; i++) {
        if (A[i] != NULL) {
            A[i]->leftSibling = A[i];
            A[i]->rightSibling = A[i];
            addToRootList(A[i]);
        }
    }
    free(roots);
}
/**
 * @brief A function that cuts the child from its tree and move it into the root list.
 * @param x The node to be made child.
 * @param y The node to be made parent.
 * @return void
 */
void cut(FibNode *x, FibNode *y) {
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
    addToRootList(x);
}
/**
 * @brief The most important function in fibonacci heap that maintains the structure with O(log n) amortized complexity.
 */
void cascadingCut(FibNode *y) {
    if (!y) return;
    FibNode *p = y->parent;
    // No parent -> in root -> no more cascading cut
    if (p != NULL) {
        if (y->childCut == false) y->childCut = true;
        else {
            cut(y, p);
            cascadingCut(p);
        }
    }
}
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
/**
 * @brief Insert a new value into the fibonacci heap
 */
void insertHeap(int const value) {
    FibNode *node = newNode(value);
    addToRootList(node);
    node_count++;
}
/**
 * @brief Extract the minimum value from the fibonacci heap
 */
void extractMin() {
    FibNode *z = min;
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
            addToRootList(curr);
            curr = next;
        } while (curr != start);
        z->children = NULL;
    }
    if (z->rightSibling == z) {
        min = NULL;
    } else {
        min = z->rightSibling;
        removeFromList(z);
        consolidate();
    }
    node_count--;
    free(z);
}
/**
 * @brief Decrease the key of a specific node (Standard CLRS implementation)
 * Time Complexity: O(1) amortized
 * @param x The pointer to the node to be modified
 * @param newValue The new value to be assigned
 */
void decreaseKey(FibNode *x, int const newValue) {
    if (!min || !x) return;
    if (newValue > x->value) {
        fprintf(stderr, "New key is greater than current key\n");
        return;
    }

    x->value = newValue;
    FibNode *y = x->parent;
    // CLRS Rule: If heap property violated, cut and cascading cut
    if (y != NULL && x->value < y->value) {
        cut(x, y);
        cascadingCut(y);
    }
    // Update global min if necessary
    if (x->value < min->value) {
        min = x;
    }
}
int comp(const void *x, const void *y) {
    FibNode const *node1 = *(FibNode **)x;
    FibNode const *node2 = *(FibNode **)y;
    if (node1->degree != node2->degree) {
        return node1->degree < node2->degree ? -1 : 1;
    }
    return node1->value < node2->value ? -1 : 1;
}
void printLevelOrder(FibNode *root) {
    if (!root) return;

    // Simple Queue for BFS (Max size 10000 based on constraints)
    FibNode* queue[10005];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    bool first = true;
    while (front < rear) {
        FibNode const *curr = queue[front++];
        if (!first) printf(" ");
        printf("%d", curr->value);
        first = false;

        // Enqueue children (already sorted by key!)
        if (curr->children) {
            FibNode *childHead = curr->children;
            FibNode *child = childHead;
            do {
                queue[rear++] = child;
                child = child->rightSibling;
            } while (child != childHead);
        }
    }
    printf("\n");
}
void printHeap() {
    if (!min) return;

    // Gather Roots
    FibNode *start = min;
    int rootCount = 0;
    if (start) {
        FibNode *c = start;
        do {
            rootCount++;
            c = c->rightSibling;
        } while (c != start);
    }

    FibNode **roots = malloc(rootCount * sizeof(FibNode *));
    FibNode *c = start;
    for (int i = 0; i < rootCount; i++) {
        roots[i] = c;
        c = c->rightSibling;
    }

    // Sort roots for printing: Degree ASC, then Key ASC
    // qsort(roots, rootCount, sizeof(FibNode *), comp);

    for (int i = 0; i < rootCount; i++) {
        printLevelOrder(roots[i]);
    }
    free(roots);
}
/**
 * @brief Delete a node from the fibonacci heap
 * @param x A pointer to the node to be deleted
 */
void deleteHeap(FibNode *x) {
    decreaseKey(x, INT_MIN);
    extractMin();
}


int main(void) {
#ifdef TEST
    setvbuf(stdout, NULL, _IONBF, 0);
    run_all_tests();
    return 0;
#else
    while (true) {
        FibNode *temp = min;
        char operation[20];
        if (scanf(" %19s", operation) != 1) break;

        if (strcmp(operation, "exit") == 0) {
            printHeap();
            break;
        } else if (strcmp(operation, "insert") == 0) {
            int value;
            if (scanf(" %d", &value) != 1) break;
            insertHeap(value);
        } else if (strcmp(operation, "decrease") == 0) {
            int key, diff;
            if (scanf(" %d %d", &key, &diff) != 2) break;
            FibNode *target = findNodeInList(min, key);
            if (target != NULL) {
                int newValue = key - diff;
                decreaseKey(target, newValue);
            }
        } else if (strcmp(operation, "extract-min") == 0) {
            extractMin();
        } else if (strcmp(operation, "delete") == 0) {
            int key;
            if (scanf(" %d", &key) != 1) break;
            FibNode *target = findNodeInList(min, key);
            if (target != NULL) deleteHeap(target);
            else fprintf(stderr, "Trying to delete an invalid key\n");
        } else {
            fprintf (stderr, "%s not defined!!!\n", operation);
        }
    }
    return 0;
#endif
}