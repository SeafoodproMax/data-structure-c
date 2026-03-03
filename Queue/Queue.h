#ifndef DATA_STRUCTURE_C_QUEUE_H
#define DATA_STRUCTURE_C_QUEUE_H

#include <stdbool.h>

typedef struct Queue Queue;

Queue *newQueue(int max_capacity);
void freeQueue(Queue *q);

bool isQueueEmpty(Queue *q);
bool isQueueFull(Queue *q);

bool pushQueue(Queue *q, int value);
bool popQueue(Queue *q, int *result);
bool frontQueue(Queue *q, int *result);

#endif
