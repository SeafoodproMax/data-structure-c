//
// Created by 林勁博 on 2025/9/24.
//

#ifndef HW1_STACK_H
#define HW1_STACK_H

#include "list.h"

struct stack {
    list List;
};
typedef struct stack stack;

void initStack(stack* s);
int isStackEmpty(stack* s);
void push(stack* s, int value);
int pop(stack* s);
void deleteStack(stack* s);

#endif //HW1_STACK_H