#ifndef DATA_STRUCTURE_C_STACK_H
#define DATA_STRUCTURE_C_STACK_H

#include <stdbool.h>

/**
 * @brief Opaque stack type.
 */
typedef struct Stack Stack;

/**
 * @brief Creates and initializes a new stack.
 *
 * @param maxSize The desired maximum capacity of the stack.
 * @return Stack* Pointer to the newly created stack; returns NULL if allocation fails or maxSize is invalid.
 */
Stack *newStack(int maxSize);

/**
 * @brief Releases all memory occupied by the stack.
 *
 * @param stack Pointer to the stack to be destroyed.
 */
void freeStack(Stack *stack);

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack Pointer to the stack.
 * @return true if the stack is empty.
 * @return false if the stack contains elements.
 */
bool isEmpty(Stack *stack);

/**
 * @brief Checks if the stack is full.
 *
 * @param stack Pointer to the stack.
 * @return true if the stack is full.
 * @return false if the stack is not full.
 */
bool isFull(Stack *stack);

/**
 * @brief Pushes a value onto the top of the stack.
 *
 * @param stack Pointer to the stack.
 * @param value The value to be pushed onto the stack.
 */
void pushStack(Stack *stack, int value);

/**
 * @brief Pops an element from the top of the stack.
 *
 * @param stack Pointer to the stack.
 */
void popStack(Stack *stack);

/**
 * @brief Peeks at the value of the top element without removing it.
 *
 * @param stack Pointer to the stack.
 * @return int The value of the top stack element, or -1 if the stack is empty.
 */
int topStack(Stack *stack);

#endif
