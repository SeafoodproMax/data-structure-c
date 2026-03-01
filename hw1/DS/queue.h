//
// Created by 林勁博 on 2025/9/27.
//

#ifndef HW1_QUEUE_H
#define HW1_QUEUE_H

#include <stdbool.h>

#include "list.h"

struct queue{
    list List;
};
typedef struct queue queue;

void initQueue(queue *q);
void freeQueue(queue *q);

bool isQueueEmpty(const queue *q);
void enqueue(queue *q, int data);
bool popQueue(queue *q, int *out);
int peekQueue(queue *q, int *out);
void printQueue(queue *q);

#endif //HW1_QUEUE_H