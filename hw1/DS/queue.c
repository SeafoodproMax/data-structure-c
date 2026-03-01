//
// Created by 林勁博 on 2025/9/27.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "queue.h"

/*
Using a doubly linked list

struct {
    list List;
};
typedef struct queue queue;
 */

void initQueue(queue *q) {
    initList(&q->List);
}
void freeQueue(queue *q) {
    deleteList(&q->List);
}

bool isQueueEmpty(const queue *q) {
    if (isListEmpty(&q->List)) return true;
    return false;
}
void enqueue(queue *q, int data) {

}
bool popQueue(queue *q, int *out) {

}
int peekQueue(queue *q, int *out) {

}
void printQueue(queue *q) {

}
