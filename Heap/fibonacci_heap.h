//
// Created by 林勁博 on 2025/12/5.
//

#ifndef TEMPLATE_FIBONACCI_HEAP_H
#define TEMPLATE_FIBONACCI_HEAP_H

#include <stdbool.h>
#include <stdlib.h>

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

extern FibNode *min;
extern FibNode *rootHead;
extern FibNode *rootTail;
extern int node_count;

int comp(const void *x, const void *y);
FibNode *newNode(int value);
void addToRootList(FibNode *node);
void removeFromList(FibNode *node);
void fibHeapLink(FibNode *y, FibNode *x);
void consolidate();
void cut(FibNode *x, FibNode *y);
void cascadingCut(FibNode *y);
FibNode *findNodeInList(FibNode *head, int key);

void insertHeap(int value);
void extractMin(void);
void decreaseKey(FibNode *x, int newValue);
void printHeap();
void deleteHeap(FibNode *x);

#endif //TEMPLATE_FIBONACCI_HEAP_H