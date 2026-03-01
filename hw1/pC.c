#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum operations {
    Error,
    moveLeft,
    moveRight,
    Insert,
    Delete
};

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    char data;
} Node;
Node* newNode(char const data) {
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
void insertListAtIndex(List* list, char const data, int const index) {
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
void deleteListAtIndex(List* list, int const index) {
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
void printList(const List* list) {
    if (list == NULL) {
        perror("List is NULL");
        return;
    }
    Node const *current = list->head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}
bool isAvailableChar(const char c) {
    return 33 <= (int)c && (int)c <= 126;
}

int main() {
    char buffer[256];
    while (true) {
        if (fgets(buffer, 256, stdin) == NULL) {
            if (feof(stdin)) break;
            perror("fgets failed");
            exit(1);
        }
        int m;
        scanf("%d", &m);
        getchar();
        List *list = initList();
        for (int i = 0; i < strlen(buffer); i++) {
            if (isAvailableChar(buffer[i])) insertListAtIndex(list, buffer[i], LIST_END);
        }
        // printList(list);
        // printf("%d\n", m);
        int pos = list->size-1;
        for (int i = 0; i < m; i++) {
            char op;
            scanf("%c", &op);
            getchar();
            switch (op) {
                case 'L':   // moveLeft
                    if (pos>=0)--pos;
                    break;
                case 'R':   // moveRight
                    if (pos< list->size-1)++pos;
                    break;
                case 'I':   // Insert a char
                    char newChar;
                    scanf("%c", &newChar);
                    getchar();
                    insertListAtIndex(list, newChar, ++pos);
                    break;
                case 'D':   // Delete a char
                    if (pos >= 0) deleteListAtIndex(list, pos--);
                    break;
                default:
                    perror("Invalid operation");
                    break;
            }
        }
        printList(list);
        list = deleteList(list);
    }
    return 0;
}