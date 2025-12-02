//
// Created by 林勁博 on 2025/11/25.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct CSLLNode CSLLNode;
struct CSLLNode {
    int value;
    CSLLNode *next;
};
typedef struct CSLL CSLL;
struct CSLL {
    CSLLNode *last;
    CSLLNode *head;
};
CSLL *newCSLL(int const value) {
    CSLL *List = malloc(sizeof(CSLL));
    CSLLNode* newNode = malloc(sizeof(CSLLNode));
    newNode->value = value;
    newNode->next = newNode; // Point to itself
    List->head = newNode;
    List->last = List->head;
    return List;
}
void freeCSLL(CSLL *List) {
    if (!List || List->last != List->head) {

    }
}