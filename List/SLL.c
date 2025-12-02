//
// Created by 林勁博 on 2025/11/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct SLLNode SLLNode;
struct SLLNode {
    int value;
    SLLNode *next;
};
SLLNode *newSLL(int const value) {
    SLLNode* newNode = malloc(sizeof(SLLNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
void freeSLL(SLLNode *head) {
    SLLNode *current = head;
    while (current != NULL) {
        SLLNode *temp = current;
        current = current->next;
        free(temp);
    }
}
SLLNode* insertSLL(SLLNode *head, int const value) {
    SLLNode *newNode = newSLL(value);
    if (!head) {
        head = newNode;
        return head;
    }
    SLLNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}
void deleteAfterSLL(SLLNode *head, int index) {
    if (!head) return;
    SLLNode *current = head;
    while (index != 0 && current->next != NULL) {
        if (index == 1) {
            SLLNode *temp = current->next;
            current->next = temp->next;
            free(temp);
            return;
        }
        current = current->next;
        index--;
    }
}
void printlnSLL(SLLNode *head) {
    SLLNode *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}