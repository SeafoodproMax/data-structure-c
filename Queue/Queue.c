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

/**
 * @brief Checks if the circular queue is empty.
 * @param q Queue pointer
 * @return true if the queue is empty
 */
bool isQueueEmpty(Queue *q) {
    // When front and rear are equal, the queue is empty.
    return q->front == q->rear;
}
/**
 * @brief Checks if the circular queue is full.
 * @param q Queue pointer
 * @return true if the queue is full
 */
bool isQueueFull(Queue *q) {
    // When (rear + 1) % MAX_SIZE equals front, the queue is full.
    return (q->rear + 1) % q->MAX_SIZE == q->front;
}

/**
 * @brief Constructor: Creates and initializes a new circular queue.
 * @param max_capacity The maximum number of elements the user wants to store (N).
 * @return Queue* Pointer to the newly created queue structure.
 */
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

/**
 * @brief Destructor: Releases the memory occupied by the queue.
 * @param q Pointer to the queue to be destroyed.
 */
void freeQueue(Queue *q) {
    if (q != NULL) {
        free(q->data); // Free the data array
        free(q);      // Free the structure itself
    }
}

/**
 * @brief Push (Enqueue) - Adds an element to the rear of the queue.
 * @param q Queue pointer
 * @param value The element value to be added.
 * @return true if enqueue was successful
 * @return false if the queue is full, enqueue failed
 */
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

/**
 * @brief Pop (Dequeue) - Removes and retrieves the element from the front of the queue.
 * @param q Queue pointer
 * @param result Pointer to store the dequeued element value.
 * @return true if dequeue was successful
 * @return false if the queue is empty, dequeue failed
 */
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

/**
 * @brief Front (Peek) - Retrieves the element at the front without removing it.
 * @param q Queue pointer
 * @param result Pointer to store the front element value.
 * @return true if successful
 * @return false if the queue is empty
 */
bool frontQueue(Queue *q, int *result) {
    if (isQueueEmpty(q)) {
        fprintf(stderr, "Error: Queue is empty, cannot peek front element.\n");
        return false;
    }

    *result = q->data[q->front];
    return true;
}