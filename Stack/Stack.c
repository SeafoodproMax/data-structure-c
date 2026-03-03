#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Default maximum stack capacity if a fixed size were to be used.
 * NOTE: The implementation now uses the size passed to newStack.
 */
#define MAX_STACK_SIZE 100000

typedef struct Stack Stack;
struct Stack {
    int *data;      /**< Dynamic array to store stack elements. */
    int top;        /**< Index of the top element (or -1 if the stack is empty). */
    int MAX_SIZE;   /**< The maximum number of elements the stack can hold. */
};

Stack *newStack(int const maxSize) {
    // Check if maxSize is valid
    if (maxSize <= 0) {
        fprintf(stderr, "Stack size must be greater than 0!!!\n");
        return NULL;
    }

    Stack *newStack = malloc(sizeof(Stack));
    if (!newStack) {
        fprintf(stderr, "Stack allocation failed!\n");
        return NULL;
    }

    // Allocate memory for the data array based on the passed maxSize
    newStack->data = malloc(sizeof(int) * maxSize);
    if (!newStack->data) {
        fprintf(stderr, "Stack data allocation failed!\n");
        free(newStack); // Clean up previously allocated structure
        return NULL;
    }

    newStack->top = -1;
    // Set MAX_SIZE to the requested capacity
    newStack->MAX_SIZE = maxSize;
    return newStack;
}

void freeStack(Stack *stack) {
    if (stack != NULL) {
        free(stack->data); // Free the data array first
        free(stack);      // Free the structure itself
    }
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

bool isFull(Stack *stack) {
    return stack->top == stack->MAX_SIZE - 1;
}

void pushStack(Stack *stack, int value) {
    if (isFull(stack)) {
        fprintf(stderr, "Error: Cannot push, stack is full (Max size: %d).\n", stack->MAX_SIZE);
        return;
    }
    // Increment the top pointer, then store the data
    ++stack->top;
    stack->data[stack->top] = value;
}

void popStack(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: Cannot pop, stack is empty.\n");
        return;
    }
    // Decrement the top pointer, logically removing the top element
    --stack->top;
}

int topStack(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!!!\n");
        return -1; // Indicate stack is empty
    }
    return stack->data[stack->top];
}
