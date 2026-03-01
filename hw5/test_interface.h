//
// Created by 林勁博 on 2025/11/28.
//

#ifndef HW5_TEST_INTERFACE_H
#define HW5_TEST_INTERFACE_H
#include <stdbool.h>
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

extern FibNode *newNode(int valye);
extern void addToRootList(FibNode *node);
extern void removeFromList(FibNode *node);
extern void fibHeapLink(FibNode *y, FibNode *x);
extern void consolidate();
extern void cut(FibNode *x, FibNode *y);
extern void cascadingCut(FibNode *y);
extern FibNode *findNodeInList(FibNode *head, int key);

extern void insertHeap(int value);
extern void extractMin(void);
extern void decreaseKey(int key, int newValue);
extern void printHeap();
extern void deleteHeap(int key);

#endif //HW5_TEST_INTERFACE_H