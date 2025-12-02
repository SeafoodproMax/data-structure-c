#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Default maximum stack capacity if a fixed size were to be used.
 * NOTE: The implementation now uses the size passed to newStack.
 */
#define MAX_STACK_SIZE 100000

/**
 * @brief Stack structure definition.
 *
 * The Stack is implemented using an array, following the Last-In, First-Out (LIFO) principle.
 */
typedef struct Stack Stack;
struct Stack {
    int *data;      /**< Dynamic array to store stack elements. */
    int top;        /**< Index of the top element (or -1 if the stack is empty). */
    int MAX_SIZE;   /**< The maximum number of elements the stack can hold. */
};

/**
 * @brief Constructor: Creates and initializes a new stack.
 *
 * @param maxSize The desired maximum capacity of the stack.
 * @return Stack* Pointer to the newly created stack; returns NULL if allocation fails or maxSize is invalid.
 */
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

/**
 * @brief Destructor: Releases all memory occupied by the stack.
 *
 * @param stack Pointer to the stack to be destroyed.
 */
void freeStack(Stack *stack) {
    if (stack != NULL) {
        free(stack->data); // Free the data array first
        free(stack);      // Free the structure itself
    }
}

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack Pointer to the stack.
 * @return true if the stack is empty (top == -1).
 * @return false if the stack contains elements.
 */
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

/**
 * @brief Checks if the stack is full.
 *
 * @param stack Pointer to the stack.
 * @return true if the stack is full (top == MAX_SIZE - 1).
 * @return false if the stack is not full.
 */
bool isFull(Stack *stack) {
    return stack->top == stack->MAX_SIZE - 1;
}

/**
 * @brief Pushes a value onto the top of the stack.
 *
 * @param stack Pointer to the stack.
 * @param value The value to be pushed onto the stack.
 */
void pushStack(Stack *stack, int value) {
    if (isFull(stack)) {
        fprintf(stderr, "Error: Cannot push, stack is full (Max size: %d).\n", stack->MAX_SIZE);
        return;
    }
    // Increment the top pointer, then store the data
    ++stack->top;
    stack->data[stack->top] = value;
}

/**
 * @brief Pops an element from the top of the stack (discards the value).
 *
 * @param stack Pointer to the stack.
 */
void popStack(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: Cannot pop, stack is empty.\n");
        return;
    }
    // Decrement the top pointer, logically removing the top element
    --stack->top;
}

/**
 * @brief Peeks at the value of the top element (without removing it).
 *
 * @param stack Pointer to the stack.
 * @return int The value of the top stack element. Returns -1 and prints an error if the stack is empty.
 */
int topStack(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!!!\n");
        return -1; // Indicate stack is empty
    }
    return stack->data[stack->top];
}
