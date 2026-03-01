//
// Created by 林勁博 on 2025/9/24.
//
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"
#include "list.h"
/*
typedef struct list {
    node* head;
    node* tail;
    size_t size;
}list;

 */

void initList(list *List) {
    List->head = NULL;
    List->tail = NULL;
    List->size = 0;
}
void deleteList(list* List) {
    node* current = List->head;
    while (current != NULL) {
        node* this = current;
        current = current->next;
        free(this);
    }
    List->head = NULL;
    List->tail = NULL;
    List->size = 0;
}
void append(list* List, int value) {
    node* newNode = createNode(value);
    newNode->next = NULL;
    if (List->head == NULL) {
        List->head = newNode;
        List->tail = newNode;
    } else {
        newNode->prev = List->tail;
        List->tail->next = newNode;
        List->tail = newNode;
    }
    List->size++;
}
void prepend(list* List, int value) {
    node* newNode = createNode(value);
    if (List->head == NULL) {
        List->head = newNode;
        List->tail = newNode;
    } else {
        newNode->next = List->head;
        List->head->prev = newNode;
        List->head = newNode;
    }
    List->size++;
}
void removeFront(list* List) {
    if (List->head == NULL) return;
    node *temp = List->head;
    List->head = List->head->next;
    if (List->head != NULL) {
        List->head->prev = NULL;
    } else {
        List->tail = NULL;
    }
    deleteNode(temp);
    List->size--;
}
void removeBack(list* List) {
    if (List->head == NULL) return;
    if (List->head == List->tail) {
        deleteNode(List->head);
        List->head = NULL;
        List->tail = NULL;
        List->size = 0;
        return;
    }
    node *temp = List->tail;
    List->tail = List->tail->prev;
    List->tail->next = NULL;
    deleteNode(temp);
    List->size--;
}
bool isListEmpty(list* List) {
    if (List->size == 0) return true;
    return false;
}