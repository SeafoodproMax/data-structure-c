//
// Created by 林勁博 on 2025/9/24.
//

#ifndef HW1_LIST_H
#define HW1_LIST_H

#include <stdlib.h>
#include "node.h"

typedef struct list {
    node* head;
    node* tail;
    size_t size;
}list;

void initList(list *List);
void deleteList(list* List);
void append(list* List, int value);
void prepend(list* List, int value);
void removeFront(list* List);
void removeBack(list* List);
bool isListEmpty(list* List);

#endif //HW1_LIST_H