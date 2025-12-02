//
// Created by 林勁博 on 2025/11/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100000

typedef struct Stack Stack;
struct Stack {
    int *data;
    int top;
    int MAX_SIZE;
};
Stack *newStack(int const maxSize) {
    if (!maxSize) {
        fprintf(stderr, "Stack size must be greater than 0!!!\n");
        return NULL;
    }
    Stack *newStack = malloc(sizeof(Stack));
    if (!newStack) {
        fprintf(stderr, "Stack allocation failed!\n");
        return NULL;
    }
    newStack->data = malloc(sizeof(int) * MAX_STACK_SIZE);
    if (!newStack->data) {
        fprintf(stderr, "Stack data allocation failed!\n");
        free(newStack);
        return NULL;
    }

    newStack->top = -1;
    newStack->MAX_SIZE = MAX_STACK_SIZE;
    return newStack;
}
void freeStack(Stack *stack) {
    free(stack->data);
    free(stack);
}
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}
bool isFull(Stack *stack) {
    return stack->top == stack->MAX_SIZE - 1;
}
void pushStack(Stack *stack, int value) {
    if (isFull(stack)) {
        fprintf(stderr, "Error: Cannot push, stack is full.\n");
        return;
    }
    ++stack->top;
    stack->data[stack->top] = value;
}
void popStack(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: Cannot pop, stack is empty.\n");
        return;
    }
    --stack->top;
}
int topStack(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!!!\n");
        return -1; // Indicate stack is empty
    }
    return stack->data[stack->top];
}
