#ifndef DATA_STRUCTURE_C_QUEUE_H
#define DATA_STRUCTURE_C_QUEUE_H

#include <stdbool.h>

/**
 * @brief Opaque circular queue type.
 */
typedef struct Queue Queue;

/**
 * @brief Creates and initializes a new circular queue.
 *
 * @param max_capacity The maximum number of elements the user wants to store.
 * @return Queue* Pointer to the newly created queue structure.
 */
Queue *newQueue(int max_capacity);

/**
 * @brief Releases the memory occupied by the queue.
 *
 * @param q Pointer to the queue to be destroyed.
 */
void freeQueue(Queue *q);

/**
 * @brief Checks if the circular queue is empty.
 *
 * @param q Queue pointer.
 * @return true if the queue is empty.
 * @return false if the queue contains elements.
 */
bool isQueueEmpty(Queue *q);

/**
 * @brief Checks if the circular queue is full.
 *
 * @param q Queue pointer.
 * @return true if the queue is full.
 * @return false if the queue can accept more elements.
 */
bool isQueueFull(Queue *q);

/**
 * @brief Adds an element to the rear of the queue.
 *
 * @param q Queue pointer.
 * @param value The element value to be added.
 * @return true if enqueue was successful.
 * @return false if the queue is full.
 */
bool pushQueue(Queue *q, int value);

/**
 * @brief Removes and retrieves the element at the front of the queue.
 *
 * @param q Queue pointer.
 * @param result Pointer to store the dequeued value.
 * @return true if dequeue was successful.
 * @return false if the queue is empty.
 */
bool popQueue(Queue *q, int *result);

/**
 * @brief Retrieves the front element without removing it.
 *
 * @param q Queue pointer.
 * @param result Pointer to store the front value.
 * @return true if successful.
 * @return false if the queue is empty.
 */
bool frontQueue(Queue *q, int *result);

#endif
