//
// Created by 林勁博 on 2025/9/24.
//

#ifndef HW1_NODE_H
#define HW1_NODE_H

struct node {
    int data;
    struct node* next;
    struct node* prev;
};
typedef struct node node;

node* createNode(int value);
void deleteNode(node* Node);

#endif //HW1_NODE_H