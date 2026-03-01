//
// Created by 林勁博 on 2025/10/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    int data;
} Node;
Node* newNode(int const data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void deleteNode(Node* node) {
    free(node);
}
typedef struct List {
    Node* head;
    Node* tail;
    size_t size;
} List;
List* initList() {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
List* deleteList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        deleteNode(temp);
    }
    free(list);
    return NULL;
}
#define LIST_END  (-10)
#define LIST_START (-11)
void insertListAtIndex(List* list, int const data, int index) {
    if (list == NULL) {
        perror("List is null");
        return;
    }

    Node* new_node = newNode(data);
    if (index != LIST_END && index != LIST_START && (index < 0 || index > (int)list->size)) {
        fprintf(stderr, "Index out of range: %d\n", index);
        free(new_node);
        return;
    }

    if (list->head == NULL) {
        list->head = list->tail = new_node;
    }
    else if (index == LIST_START || index == 0) {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    else if (index == LIST_END || index == (int)list->size) {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) current = current->next;
        new_node->next = current->next;
        new_node->prev = current;
        if (current->next != NULL)
            current->next->prev = new_node;
        current->next = new_node;
    }
    list->size++;
}
void deleteListAtIndex(List* list, int index) {
    if (list == NULL) {
        perror("List is NULL");
        return;
    }
    if (list->head == NULL) {
        fprintf(stderr, "Warning: delete on empty list ignored.\n");
        return;
    }
    if (index != LIST_END && index != LIST_START && (index < 0 || index >= (int)list->size)) {
        fprintf(stderr, "Index out of range: %d\n", index);
        return;
    }

    if (index == LIST_START || index == 0) {
        Node* current = list->head;
        list->head = current->next;
        if (list->head != NULL)
            list->head->prev = NULL;
        else
            list->tail = NULL;
        deleteNode(current);
    }
    else if (index == LIST_END || index == (int)list->size - 1) {
        Node* current = list->tail;
        if (current->prev != NULL)
            current->prev->next = NULL;
        else
            list->head = NULL;
        list->tail = current->prev;
        deleteNode(current);
    }
    else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) current = current->next;
        Node* temp = current->next;
        current->next = temp->next;
        if (temp->next != NULL)
            temp->next->prev = current;
        else
            list->tail = current;
        deleteNode(temp);
    }
    list->size--;
}
void printList(List* list) {
    if (list == NULL) {
        perror("List is NULL");
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
enum operation {
    InsertAtHead = 1,
    InsertAtTail,
    AppendAtK,
    PrependAtK,
    DeleteAtK,
    MoveKToHead,
    MoveKToTail,
};
enum operation convertToOperation(char const* str) {
    if (strcmp(str, "H") == 0) return InsertAtHead;
    if (strcmp(str, "T") == 0) return InsertAtTail;
    if (strcmp(str, "A") == 0) return AppendAtK;
    if (strcmp(str, "B") == 0) return PrependAtK;
    if (strcmp(str, "D") == 0) return DeleteAtK;
    if (strcmp(str, "MH") == 0) return MoveKToHead;
    if (strcmp(str, "MT") == 0) return MoveKToTail;
    return -1;
}
bool isInt(const char c) {
    return (48 <= (int)c && (int)c <= 57);
}
int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    int n, q;
    {
        char buffer[100];
        fgets(buffer, 100, stdin);
        sscanf(buffer, "%d %d", &n, &q);
    }
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d ", &arr[i]);
    }
    getchar();
    List* list = initList();
    for (int i = 0; i < n; i++) {
        insertListAtIndex(list, arr[i], LIST_END);
    }
    printList(list);
    for (int i = 0; i < q; i++) {
        char buffer[100], word[10], x, k;
        int offset = 0, read;
        enum operation op;
        fgets(buffer, 100, stdin);
        int j = 0;
        while (sscanf(buffer, "%s %n", word, &read)) {
            if (j++ == 0)   op = convertToOperation(word);
            if (j++ == 1)   x = atoi(word);
            if (j++ == 2)   k = atoi(word);
            offset += read;
        }
        switch (op) {
            case InsertAtHead:
                insertListAtIndex(list, xk[0], LIST_START);
                break;
            case InsertAtTail:
                insertListAtIndex(list, xk[0], LIST_END);
                break;
            case AppendAtK:
                insertListAtIndex(list, xk[0], xk[1]);
                break;
            case PrependAtK:
                insertListAtIndex(list, xk[0], xk[1]-1);
                break;
            case DeleteAtK:
                deleteListAtIndex(list, xk[0]-1);
                break;
            case MoveKToHead:
                deleteListAtIndex(list, xk[0]-1);
                insertListAtIndex(list, xk[0], LIST_START);
                break;
            case MoveKToTail:
                deleteListAtIndex(list, xk[0]-1);
                insertListAtIndex(list, xk[0], LIST_END);
                break;
            default:
                perror("Invalid operation");
                return 1;
        }
    }
    printList(list);
    deleteList(list);
    return 0;
}