//
// Created by 林勁博 on 2025/12/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Default maximum capacity
#define DEFAULT_MAX_QUEUE_SIZE 100000

// Circular Queue Structure Definition
typedef struct Queue {
    int *data;
    int front; // Index of the front element
    int rear;  // Index where the next element will be inserted
    int MAX_SIZE; // Array size (capacity + 1)
} Queue;

bool isQueueEmpty(Queue *q) {
    // When front and rear are equal, the queue is empty.
    return q->front == q->rear;
}
bool isQueueFull(Queue *q) {
    // When (rear + 1) % MAX_SIZE equals front, the queue is full.
    return (q->rear + 1) % q->MAX_SIZE == q->front;
}

Queue* newQueue(const int max_capacity) {
    if (max_capacity <= 0) {
        fprintf(stderr, "Error: Queue capacity must be greater than 0.\n");
        return NULL;
    }

    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for Queue structure.\n");
        return NULL;
    }

    // Allocate array size for N + 1 elements to distinguish full from empty
    q->MAX_SIZE = max_capacity + 1;
    q->data = (int*)malloc(sizeof(int) * q->MAX_SIZE);

    if (q->data == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for data array.\n");
        free(q);
        return NULL;
    }

    // Initialize front and rear to 0 (queue is empty)
    q->front = 0;
    q->rear = 0;

    return q;
}

void freeQueue(Queue *q) {
    if (q != NULL) {
        free(q->data); // Free the data array
        free(q);      // Free the structure itself
    }
}

bool pushQueue(Queue *q, int value) {
    if (isQueueFull(q)) {
        fprintf(stderr, "Error: Queue is full, cannot push element %d.\n", value);
        return false;
    }

    // Place the new element at the index pointed to by rear
    q->data[q->rear] = value;

    // Update rear using modulo arithmetic for circular wrap-around
    q->rear = (q->rear + 1) % q->MAX_SIZE;

    return true;
}

bool popQueue(Queue *q, int *result) {
    if (isQueueEmpty(q)) {
        fprintf(stderr, "Error: Queue is empty, cannot pop element.\n");
        return false;
    }

    // Retrieve the element pointed to by front
    *result = q->data[q->front];

    // Update front using modulo arithmetic for circular wrap-around
    q->front = (q->front + 1) % q->MAX_SIZE;

    return true;
}

bool frontQueue(Queue *q, int *result) {
    if (isQueueEmpty(q)) {
        fprintf(stderr, "Error: Queue is empty, cannot peek front element.\n");
        return false;
    }

    *result = q->data[q->front];
    return true;
}
