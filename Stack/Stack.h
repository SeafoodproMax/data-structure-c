#ifndef DATA_STRUCTURE_C_STACK_H
#define DATA_STRUCTURE_C_STACK_H

#include <stdbool.h>

typedef struct Stack Stack;

Stack *newStack(int maxSize);
void freeStack(Stack *stack);

bool isEmpty(Stack *stack);
bool isFull(Stack *stack);

void pushStack(Stack *stack, int value);
void popStack(Stack *stack);
int topStack(Stack *stack);

#endif
