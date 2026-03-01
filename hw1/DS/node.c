//
// Created by 林勁博 on 2025/9/24.
//
#include <stdlib.h>
#include "node.h"

/*
struct node {
    int data;
    struct node* next;
    struct node* prev;
};
typedef struct node node;

*/

node* createNode(int value) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
void deleteNode(node* Node) {
    free(Node);
}