//
// Created by 林勁博 on 2025/9/24.
//
#include <stdio.h>

#include "list.h"
#include "stack.h"

/*
struct stack {
    list List;
};
typedef struct stack stack;

*/

void initStack(stack* s) {
    initList(&s->List);
}
int isStackEmpty(stack* s) {
    return s->List->size == 0;
}
void push(stack* s, int value) {
    prepend(&s->List, value);
}
int pop(stack* s) {
    if (isStackEmpty(s)) {
        printf("Stack underflow!\n");
        exit(1);
    }
    int value = s->List.head->data;
    removeFront(&s->List);
    return value;
}
void deleteStack(stack *s) {
    deleteList(&s->List);
}